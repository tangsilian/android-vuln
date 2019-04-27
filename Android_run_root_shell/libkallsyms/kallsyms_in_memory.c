#define _LARGEFILE64_SOURCE
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <endian.h>

#include "kallsyms_in_memory.h"

#ifndef le32toh
#define le32toh         letoh32
#endif

#ifndef le16toh
#define le16toh         letoh16
#endif

#ifdef __LP64__
#define letoh           le64toh
#define htole           htole64
#else
#define letoh           le32toh
#define htole           htole32
#endif


#define PATTERN_MAX     8

static bool verbose_output;

#define DBGPRINT(fmt...) do { if (verbose_output) { fprintf(stderr, fmt); } } while (0)

#define ARRAY_SIZE(n) (sizeof (n) / sizeof (*n))

struct _kallsyms {
  unsigned long  num_syms;
  unsigned long *addresses;
  uint8_t       *names;
  uint8_t       *token_table;
  uint16_t      *token_index;
  unsigned long *markers;
  int            has_type_table;
};

/*
 * Expand a compressed symbol data into the resulting uncompressed string,
 * given the offset to where the symbol is in the compressed stream.
 */
static unsigned int
kallsyms_in_memory_expand_symbol(kallsyms *info, unsigned int off, char *result)
{
  int len, skipped_type_marker = info->has_type_table;
  const uint8_t *tptr, *data;

  /* Get the compressed symbol length from the first symbol byte. */
  data = &info->names[off];
  len = *data;
  data++;

  /*
   * Update the offset to return the offset for the next symbol on
   * the compressed stream.
   */
  off += len + 1;

  /*
   * For every byte on the compressed symbol data, copy the table
   * entry for that byte.
   */
  while (len) {
    tptr = &info->token_table[le16toh(info->token_index[*data])];
    data++;
    len--;

    while (*tptr) {
      if (skipped_type_marker) {
        *result = *tptr;
        result++;
      }
      else {
        skipped_type_marker = 1;
      }

      tptr++;
    }
  }

  *result = '\0';

  /* Return to offset to the next symbol. */
  return off;
}

/* Lookup the address for this symbol. Returns 0 if not found. */
unsigned long
kallsyms_in_memory_lookup_name(kallsyms *info, const char *name)
{
  char namebuf[1024];
  unsigned long i;
  unsigned int off;

  if (!info) {
    return 0;
  }

  for (i = 0, off = 0; i < info->num_syms; i++) {
    off = kallsyms_in_memory_expand_symbol(info, off, namebuf);
    if (strcmp(namebuf, name) == 0) {
      return letoh(info->addresses[i]);
    }
  }
  return 0;
}

bool
kallsyms_in_memory_lookup_names(kallsyms *info, const char *name,
                                unsigned long *addresses, size_t n_addresses)
{
  char namebuf[1024];
  unsigned long i, count;
  unsigned int off;

  if (!info) {
    return false;
  }

  for (i = 0, off = 0, count = 0;
       i < info->num_syms && count < n_addresses;
       i++) {
    off = kallsyms_in_memory_expand_symbol(info, off, namebuf);
    if (strcmp(namebuf, name) == 0) {
      addresses[count] = letoh(info->addresses[i]);
      count++;
    }
  }
  if (!count) {
    return false;
  }

  return true;
}

/* Lookup the symbol for this address. Returns NULL if not found. */
const char *
kallsyms_in_memory_lookup_address(kallsyms *info, unsigned long address)
{
  static char namebuf[1024];
  unsigned long i;
  unsigned int off;

  if (!info) {
    return NULL;
  }

  for (i = 0, off = 0; i < info->num_syms; i++) {
    off = kallsyms_in_memory_expand_symbol(info, off, namebuf);
    if (letoh(info->addresses[i]) == address) {
      return namebuf;
    }
  }
  return NULL;
}

static const unsigned long const pattern_kallsyms_addresses_1[PATTERN_MAX] = {
#ifdef __LP64__
  0xffffffc000080000, // _text
  0xffffffc000080040, // stext
  0xffffffc000080080, // __h_error
  0xffffffc000080080, // __h_error_p
  0xffffffc0000800c0, // __h_enable_mmu
  0xffffffc0000800d8, // __h_turn_mmu_on
  0xffffffc0000800e4, // __vet_fdt
#else
  //00000000, //  __vectors_start
  0x00001000, // __stubs_start
  0x00001004, // vector_rst
  0x00001020, // vector_irq
  0x000010a0, // vector_dabt
#endif
  0
};

static const unsigned long const pattern_kallsyms_addresses_2[PATTERN_MAX] = {
  0xc0008000, // __init_begin
  0xc0008000, // _sinittext
  0xc0008000, // stext
  0xc0008000, // _text
  0
};

static const unsigned long const pattern_kallsyms_addresses_3[PATTERN_MAX] = {
  0xc0008000, // stext
  0xc0008000, // _text
  0
};

static const unsigned long const pattern_kallsyms_addresses_4[PATTERN_MAX] = {
  0xc00081c0, // asm_do_IRQ
  0xc00081c0, // _stext
  0xc00081c0, // __exception_text_start
  0
};

static const unsigned long const pattern_kallsyms_addresses_5[PATTERN_MAX] = {
  0xc0008180, // asm_do_IRQ
  0xc0008180, // _stext
  0xc0008180, // __exception_text_start
  0
};

static const unsigned long const pattern_kallsyms_addresses_6[PATTERN_MAX] = {
  0xc0100000, // asm_do_IRQ
  0xc0100000, // _stext
  0xc0100000, // __exception_text_start
  0xc0100004, // do_undefinstr
  0
};

static const unsigned long const * const pattern_kallsyms_addresses[] = {
  pattern_kallsyms_addresses_1,
  pattern_kallsyms_addresses_2,
  pattern_kallsyms_addresses_3,
  pattern_kallsyms_addresses_4,
  pattern_kallsyms_addresses_5,
  pattern_kallsyms_addresses_6,
};

static unsigned long *
search_pattern(unsigned long *base, unsigned long count, const unsigned long *const pattern)
{
  unsigned long *addr = base;
  unsigned long i;
  int pattern_count;

  for (pattern_count = 0; pattern[pattern_count]; pattern_count++) {
    ;
  }

  for (i = 0; i < count - pattern_count; i++) {
    if(addr[i] != pattern[0]) {
      continue;
    }

    if (memcmp(&addr[i], pattern, sizeof (pattern[0]) * pattern_count) == 0) {
      return &addr[i];
    }
  }
  return 0;
}

static bool
is_type_table(const unsigned int *mem, unsigned long length)
{
  int i;

  if (length < 256 * 4) {
    return false;
  }

  for (i = 0; i < 256; i++) {
    unsigned int data = mem[i] & ~0x20202020;

    if (data != 0x54545454) {
      return false;
    }
  }

  return true;
}

static int
get_kallsyms_in_memory_addresses(kallsyms *info, unsigned long *mem, unsigned long length, unsigned long offset)
{
  unsigned long *addr = mem;
  unsigned long *end = (unsigned long*)((unsigned long)mem + length);

  if (!info) {
    return -1;
  }

  while (addr < end) {
    unsigned long *search = addr;
    unsigned long i;

    // get kallsyms_in_memory_addresses pointer
    for (i = 0; i < sizeof (pattern_kallsyms_addresses) / sizeof (pattern_kallsyms_addresses[0]); i++) {
      unsigned long pattern_le[PATTERN_MAX];
      int j;

      for (j = 0; j < PATTERN_MAX; j++) {
          pattern_le[j] = htole(pattern_kallsyms_addresses[i][j]);
      }

      addr = search_pattern(search, end - search, pattern_le);
      if (addr) {
        break;
      }
    }

    if (!addr) {
        return 0;
    }

    info->addresses = addr;

    // search end of kallsyms_in_memory_addresses
    unsigned long n=0;
#ifdef __LP64__
    while (letoh(addr[0]) <= 0xffffffc000080000LL) {
#else
    while (letoh(addr[0]) <= 0xc0000000) {
#endif
      n++;
      addr++;
      if (addr >= end) {
        return 0;
      }
    }
#ifdef __LP64__
    while (letoh(addr[0]) > 0xffffffc000080000LL) {
#else
    while (letoh(addr[0]) > 0xc0000000) {
#endif
      n++;
      addr++;
      if (addr >= end) {
        return 0;
      }
    }

    // skip there is filled by 0x0
    while (addr[0] == 0x00000000) {
      addr++;
      if (addr >= end) {
        return 0;
      }
    }

    info->num_syms = letoh(addr[0]);
    addr++;
    if (addr >= end) {
      return 0;
    }

    // adjust if it has one more address that equals zero
    if (info->num_syms == n + 1) {
      if (info->addresses > mem
       && info->addresses[-1] == 0) {
        info->addresses--;
	n++;
      }
    }

    DBGPRINT("[+]kallsyms_addresses=%08lx\n", (unsigned long)info->addresses + offset);
    DBGPRINT("  count=%08x\n", (unsigned int)n);
    DBGPRINT("[+]kallsyms_num_syms=%08x\n", (unsigned int)info->num_syms);

    // check kallsyms_in_memory_num_syms
    if (info->num_syms != n) {
      continue;
    }

    // skip there is filled by 0x0
    while (addr[0] == 0x00000000) {
      addr++;
      if (addr >= end) {
        return 0;
      }
    }

    info->names = (uint8_t*)addr;
    DBGPRINT("[+]kallsyms_names=%08lx\n", (unsigned long)info->names + offset);

    // search end of kallsyms_in_memory_names
    unsigned int off;
    for (i = 0, off = 0; i < info->num_syms; i++) {
      int len = info->names[off];
      off += len + 1;
      if (&info->names[off] >= (uint8_t*)end) {
        return 0;
      }
    }

    // adjust
#ifdef __LP64__
    addr = (unsigned long*)((((unsigned long)&info->names[off]-1)|0x7)+1);
#else
    addr = (unsigned long*)((((unsigned long)&info->names[off]-1)|0x3)+1);
#endif
    if (addr >= end) {
      return 0;
    }

    // skip there is filled by 0x0
    while (addr[0] == 0x00000000) {
      addr++;
      if (addr >= end) {
        return 0;
      }
    }

    if (is_type_table((void *)addr, (unsigned long)end - (unsigned long)addr)) {
      DBGPRINT("[+]kallsyms_type_table=%08lx\n", (unsigned long)addr + offset);
      info->has_type_table = 1;

      // skip kallsyms_type_table if exist
      while (addr[0] != 0x00000000) {

	addr++;
	if (addr >= end) {
	  return 0;
	}
      }

      // skip there is filled by 0x0
      while (addr[0] == 0x00000000) {
	addr++;
	if (addr >= end) {
	  return 0;
	}
      }
    }

    // but kallsyms_in_memory_markers shoud be start 0x00000000
    addr--;

    info->markers = addr;
    DBGPRINT("[+]kallsyms_markers=%08lx\n", (unsigned long)info->markers + offset);

    // end of kallsyms_in_memory_markers
    addr = &info->markers[((info->num_syms-1)>>8)+1];
    if (addr >= end) {
      return 0;
    }

    // skip there is filled by 0x0
    while (addr[0] == 0x00000000) {
      addr++;
      if (addr >= end) {
        return 0;
      }
    }

    info->token_table = (uint8_t*)addr;
    DBGPRINT("[+]kallsyms_token_table=%08lx\n", (unsigned long)info->token_table + offset);

    // search end of kallsyms_in_memory_token_table
    i = 0;
    while (info->token_table[i] != 0x00 || info->token_table[i+1] != 0x00) {
      i++;
      if (&info->token_table[i-1] >= (uint8_t*)end) {
        return 0;
      }
    }

    // skip there is filled by 0x0
    while (info->token_table[i] == 0x00) {
      i++;
      if (&info->token_table[i-1] >= (uint8_t*)end) {
        return 0;
      }
    }

    // but kallsyms_in_memory_markers shoud be start 0x0000
    info->token_index = (uint16_t*)&info->token_table[i-2];
    DBGPRINT("[+]kallsyms_token_index=%08lx\n", (unsigned long)info->token_index + offset);

    return 1;
  }
  return 0;
}

kallsyms *
kallsyms_in_memory_init(unsigned long *mem, size_t len)
{
  kallsyms *info;
#ifdef __LP64__
  unsigned long mmap_offset = 0xffffffc000080000LL - (unsigned long)mem;
#else
  unsigned long mmap_offset = 0xc0008000 - (unsigned long)mem;
#endif
  DBGPRINT("[+]mmap\n");
  DBGPRINT("  mem=%08lx length=%08x offset=%08lx\n", (unsigned long)mem, (unsigned int)len, (unsigned long)mmap_offset);

  info = calloc(sizeof(*info), 1);
  if (info == NULL) {
    return NULL;
  }

  int ret = get_kallsyms_in_memory_addresses(info, mem, len, mmap_offset);
  if (!ret) {
    fprintf(stderr, "kallsyms_in_memory_addresses search failed\n");
    free(info);
    return NULL;
  }

  //kallsyms_in_memory_print_all();
  DBGPRINT("[+]kallsyms_lookup_name\n");

  return info;
}

bool
is_address_in_kallsyms_table(kallsyms *info, void *mapped_address)
{
  DBGPRINT("check %p <= %p <= %p\n",
           info->addresses, mapped_address, &info->addresses[info->num_syms]);

  if (mapped_address < (void *)info->addresses)
    return false;

  if (mapped_address > (void *)&info->addresses[info->num_syms])
    return false;

  return true;
}

void
kallsyms_in_memory_print_all_to_file(kallsyms *info, FILE *fp)
{
  char namebuf[1024];
  unsigned long i;
  unsigned int off;

  if (!info) {
    return;
  }

  for (i = 0, off = 0; i < info->num_syms; i++) {
    off = kallsyms_in_memory_expand_symbol(info, off, namebuf);
    fprintf(fp, "%08lx %s\n", (unsigned long)letoh(info->addresses[i]), namebuf);
  }
  return;
}

void
kallsyms_in_memory_print_all(kallsyms *info)
{
  if (!info) {
    return;
  }
  kallsyms_in_memory_print_all_to_file(info, stdout);
}

void
kallsyms_in_memory_set_verbose(bool verbose)
{
  verbose_output = verbose;
}

void
kallsyms_in_memory_free(kallsyms *info)
{
  if (info) {
    free(info);
  }
}

#if 0
static bool
do_kallsyms_in_memory(void)
{
  bool ret;
  void *address;

  if (!map_kernel_memory()) {
    printf("Failed to mmap due to %s.\n", strerror(errno));

    return false;
  }

#ifdef __LP64__
  address = convert_to_kernel_mapped_address((void *)0xffffffc000080000LL);
#else
  address = convert_to_kernel_mapped_address((void *)0xc0008000);
#endif
  ret = get_kallsyms_in_memory(address, KERNEL_MEMORY_SIZE);

  unmap_kernel_memory();
  return ret;
}

int
main(int argc, char **argv)
{
  if (!do_kallsyms_in_memory()) {
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
#endif
/*
vi:ts=2:nowrap:ai:expandtab:sw=2
*/
