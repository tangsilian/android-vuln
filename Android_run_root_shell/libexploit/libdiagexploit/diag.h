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
#ifndef DIAG_H
#define DIAG_H

#include <stdbool.h>

struct diag_values {
  unsigned int address;
  unsigned short value;
  unsigned short original_value;
};

bool diag_inject(struct diag_values *data, int data_length);
bool diag_inject_with_fd(struct diag_values *data, int data_length, int fd);
bool diag_is_supported(void);
bool diag_run_exploit(struct diag_values *data, int data_length,
                      bool(*exploit_callback)(void* user_data), void *user_data);

#endif /* DIAG_H */
/*
vi:ts=2:nowrap:ai:expandtab:sw=2
*/
