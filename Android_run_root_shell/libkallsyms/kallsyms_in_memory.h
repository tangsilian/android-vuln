#ifndef __KALLSYMSPRINT_H__
#define __KALLSYMSPRINT_H__

#include <stdbool.h>
#include <stdio.h>

typedef struct _kallsyms kallsyms;

kallsyms *     kallsyms_in_memory_init          (unsigned long *mem, size_t len);
void           kallsyms_in_memory_free          (kallsyms *kallsyms);
unsigned long  kallsyms_in_memory_lookup_name   (kallsyms *kallsyms, const char *name);
bool           kallsyms_in_memory_lookup_names  (kallsyms *kallsyms, const char *name,
                                                 unsigned long *addresses, size_t n_addresses);
const char    *kallsyms_in_memory_lookup_address(kallsyms *kallsyms, unsigned long address);

bool is_address_in_kallsyms_table(kallsyms *kallsyms, void *mapped_address);

void kallsyms_in_memory_set_verbose(bool verbose);
void kallsyms_in_memory_print_all(kallsyms *kallsyms);
void kallsyms_in_memory_print_all_to_file(kallsyms *kallsyms, FILE *fp);

#endif /* __KALLSYMSPRINT_H__ */

/*
vi:ts=2:nowrap:ai:expandtab:sw=2
*/
