#define __ASSEMBLY__
#include  <linux/linkage.h>

.extern sayhello


ENTRY(shell_code2)
                      ldr r0, [pc , #4]
                      STMFD  SP!, {R0}
                      LDMFD   SP!, {PC}
 .byte 0xee, 0xee, 0xee, 0xee

