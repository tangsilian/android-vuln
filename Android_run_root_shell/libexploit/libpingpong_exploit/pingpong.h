#ifndef PINGPONG_H
#define PINGPONG_H

#include <stdbool.h>

#define PINGPONG_MAX_REQUEST_COUNT	1024

extern bool pingpong_read_value_at_address(unsigned long address, int *value);
extern bool pingpong_read_values_at_address(unsigned long address, int *values, int count);
extern bool pingpong_write_value_at_address(unsigned long address, int value);
extern bool pingpong_write_values_at_address(unsigned long address, const int *values, int count);

extern bool pingpong_run_exploit(unsigned long int address, int value,
                                 bool(*exploit_callback)(void* user_data), void *user_data);


#endif /* PINGPONG_H */
