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
#ifndef PTMX_H
#define PTMX_H

#include <stdbool.h>
#include <stdio.h>

#define PTMX_DEVICE "/dev/ptmx"

typedef struct _find_ptmx_fops_hint_t {
  unsigned long int ptmx_open_address;
  unsigned long int tty_release_address;
  unsigned long int tty_fasync_address;
} find_ptmx_fops_hint_t;

extern bool setup_ptmx_fops_address(void);
extern bool setup_ptmx_fops_mmap_address(void);
extern bool setup_ptmx_fops_fsync_address(void);

extern bool setup_ptmx_fops_address_in_memory(void *mem, size_t length,
                                              find_ptmx_fops_hint_t  *hint);

extern void *ptmx_fops;
extern unsigned long int ptmx_fops_mmap_address;
extern unsigned long int ptmx_fops_fsync_address;

#endif /* PTMX_H */
/*
vi:ts=2:nowrap:ai:expandtab:sw=2
*/
