#include <string.h>
#include <memory.h>
#include "ptmx.h"
#include "kallsyms.h"
#include "device_database/device_database.h"

void *ptmx_fops;
unsigned long int ptmx_fops_mmap_address;
unsigned long int ptmx_fops_fsync_address;

bool
setup_ptmx_fops_address(void)
{
  if (ptmx_fops) {
    return true;
  }

  ptmx_fops = (void *)device_get_symbol_address(DEVICE_SYMBOL(ptmx_fops));

  if (!ptmx_fops && kallsyms_exist()) {
    ptmx_fops = kallsyms_get_symbol_address("ptmx_fops");
  }

  return !!ptmx_fops;
}

bool
setup_ptmx_fops_mmap_address(void)
{
  if (!ptmx_fops) {
    setup_ptmx_fops_address();
    if (!ptmx_fops) {
      return false;
    }
  }

  ptmx_fops_mmap_address = (unsigned long int)ptmx_fops + 0x28;
  return true;
}

bool
setup_ptmx_fops_fsync_address(void)
{
  if (!ptmx_fops) {
    setup_ptmx_fops_address();
    if (!ptmx_fops) {
      return false;
    }
  }

  ptmx_fops_fsync_address = (unsigned long int)ptmx_fops + 0x38;
  return true;
}

bool
setup_ptmx_fops_address_in_memory(void *mem, size_t length, find_ptmx_fops_hint_t  *hint)
{
  int i;

  for (i = 0x24; i < length - 0x40; i += 4) {
    unsigned long int *address = mem + i;

    if (address[2] != hint->ptmx_open_address) {
      continue;
    }

    if (address[4] != hint->tty_release_address) {
      continue;
    }

    if (address[7] != hint->tty_fasync_address) {
      continue;
    }

    ptmx_fops = (void *)convert_to_kernel_address(address, mem) - 0x24;
    return true;
  }

  return false;
}
