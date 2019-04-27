#include "perf_swevent.h"
#include "perf_event.h"

int
perf_swevent_write_value_at_address(unsigned long int address, int value)
{
  return perf_event_write_value_at_address(address, value);
}

void
perf_swevent_reap_child_process(int number)
{
  perf_event_reap_child_process(number);
}

bool
perf_swevent_run_exploit(unsigned long int address, int value,
                         bool(*exploit_callback)(void* user_data), void *user_data)
{
  return perf_event_run_exploit(address, value, exploit_callback, user_data);
}

/*
vi:ts=2:nowrap:ai:expandtab:sw=2
*/
