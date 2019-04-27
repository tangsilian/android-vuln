#ifndef ACDB_H
#define ACDB_H

#include <stdbool.h>

extern bool acdb_write_value_at_address(unsigned long address, int value);

extern bool acdb_run_exploit(unsigned long int address, int value,
                             bool(*exploit_callback)(void* user_data), void *user_data);


#endif /* ACDB_H */
