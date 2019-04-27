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
#ifndef MM_H
#define MM_H

#include <stdbool.h>
#include <stdio.h>
#include <libexploit/exploit.h>

struct file;

typedef struct {
  unsigned long pgprot;
} pgprot_t;

struct vm_area_struct {
  void *vm_mm;
  unsigned long vm_start, vm_end;
  void *vm_next, *vm_prev;
  pgprot_t vm_page_prot;
  /* ... */
};

typedef bool (*memory_callback_t)(void *mem, size_t length);

extern bool setup_remap_pfn_range_address(void);
extern bool run_with_mmap(memory_callback_t callback);
extern bool run_with_memcpy(memory_callback_t callback);

extern void set_kernel_phys_offset(unsigned long int offset);
extern void *convert_to_kernel_address(void *address, void *mmap_base_address);
extern void *convert_to_mmaped_address(void *address, void *mmap_base_address);

extern int (*remap_pfn_range)(struct vm_area_struct *, unsigned long addr,
                              unsigned long pfn, unsigned long size, pgprot_t);

#endif /* MM_H */
/*
vi:ts=2:nowrap:ai:expandtab:sw=2
*/
