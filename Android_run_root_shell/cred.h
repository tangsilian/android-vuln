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
#ifndef CREDS_H
#define CREDS_H

#include <stdbool.h>
#include <stdio.h>

struct cred;
struct task_struct;

typedef struct cred *(*prepare_kernel_cred_t)(struct task_struct *);
typedef int (*commit_creds_t)(struct cred *);

extern bool setup_prepare_kernel_cred_address();
extern bool setup_commit_creds_address();

extern bool setup_prepare_kernel_cred_address_in_memory(void *mem, size_t length);
extern bool setup_commit_creds_address_in_memory(void *mem, size_t length);

extern prepare_kernel_cred_t prepare_kernel_cred;
extern commit_creds_t commit_creds;

#endif /* CREDS_H */
/*
vi:ts=2:nowrap:ai:expandtab:sw=2
*/
