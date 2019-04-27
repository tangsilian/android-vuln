#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/reg.h>

int main(int argc, char *argv[])
{
	int fd[2];
	pipe2(fd, O_NONBLOCK);
	int child = fork();
	if (child) {
		close(fd[1]);
		char buf;
		for (;;) {
			wait(NULL);
			if (read(fd[0], &buf, 1) > 0)
				break;
			ptrace(PTRACE_SYSCALL, child, NULL, NULL);
		}
		
		struct user_regs_struct regs;
		for (;;) {
			ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
			wait(NULL);
			ptrace(PTRACE_GETREGS, child, NULL, &regs);
#if defined(__i386__)
#define instruction_pointer regs.eip
#define upper_bound 0xb0000000
#elif defined(__x86_64__)
#define instruction_pointer regs.rip
#define upper_bound 0x700000000000
#else
#error "That platform is not supported."
#endif
			if (instruction_pointer < upper_bound) {
				unsigned long instruction = ptrace(PTRACE_PEEKTEXT, child, instruction_pointer, NULL);
				if ((instruction & 0xffff) == 0x25ff /* jmp r/m32 */) {
					printf("0x%lx\n", instruction_pointer);
					break;
				}
			}
		}
	} else {
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		close(fd[0]);
		dup2(fd[1], 2);
		execl("/bin/su", "su", "not-a-valid-user", NULL);
	}
	return 0;
}
