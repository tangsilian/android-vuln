#ifndef VROOT_H
#define VROOT_H

#include <stdbool.h>

extern bool vroot_write_value_at_address(unsigned long address, int value);

extern bool vroot_run_exploit(unsigned long int address, int value,
                             bool(*exploit_callback)(void* user_data), void *user_data);


#endif /* VROOT_H */
