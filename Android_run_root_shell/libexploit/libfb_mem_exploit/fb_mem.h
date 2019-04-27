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
#ifndef FB_MEM_H
#define FB_MEM_H

#include <stdbool.h>

void fb_mem_set_kernel_phys_offset(int offset);
bool fb_mem_write_value_at_address(unsigned long int address, int value);
bool fb_mem_run_exploit(bool(*exploit_callback)(void *mmap_base_address, void *user_data),
                        void *user_data);
void *fb_mem_mmap(int *fd);
int   fb_mem_munmap(void *address, int fd);
void *fb_mem_convert_to_mmaped_address(void *address, void *mmap_base_address);

#endif /* FB_MEM_H */
/*
vi:ts=2:nowrap:ai:expandtab:sw=2
*/
