#ifndef FUTEX_H
#define FUTEX_H

#include <stdbool.h>

#define FUTEX_REQUEUE_MAX_REQUEST_COUNT	1024

extern bool futex_read_value_at_address(unsigned long address, int *value);
extern bool futex_read_values_at_address(unsigned long address, int *values, int count);
extern bool futex_write_value_at_address(unsigned long address, int value);
extern bool futex_write_values_at_address(unsigned long address, const int *values, int count);

extern bool futex_run_exploit(unsigned long int address, int value,
                             bool(*exploit_callback)(void* user_data), void *user_data);


#endif /* FUTEX_H */
