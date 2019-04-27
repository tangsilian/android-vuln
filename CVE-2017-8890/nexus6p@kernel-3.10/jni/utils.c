#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <err.h>
#include "utils.h"
#define HEXDUMP_COLS 16

static void die __P((int));
static void die(ret) int ret;
{
  fprintf(stderr, ": %d", __LINE__);
  perror(NULL);
  exit(ret);
}

void hex_cinclude(void *mem, size_t	length)
{
	FILE *fp, *fpo = stdout;
	char *array_name = "dump";
	int c, p = c = 0, cols = 12;
	char hexxa[] = "0123456789abcdef0123456789ABCDEF", *hexx = hexxa;	

	/* print dump array start section */ 
	{
	  if (fprintf(fpo, "unsigned char %s", array_name) < 0)
	    die(3);
	  if (fputs("[] = {\n", fpo) == EOF)
	    die(3);
	}
	/* print the content */
    while ( p < length) 
	{
	  c = ((char*)mem)[p];
	  if (fprintf(fpo, (hexx == hexxa) ? "%s0x%02x" : "%s0X%02X",
		(p % cols) ? ", " : &",\n  "[2*!p],  c) < 0)
	    die(3);
	  p++;
	}
	/* print the epilogue */
    if (p && fputs("\n", fpo) == EOF)
	die(3);
//    if (fputs(&"};\n"[3 * (fp == stdin)], fpo) == EOF)
	if (fputs("};\n", fpo) == EOF)
	die(3);
	/* calculate dump array size */ 
	{
	  if (fprintf(fpo, "unsigned int %s", array_name) < 0)
	    die(3);
	  if (fprintf(fpo, "_len = %d;\n", p) < 0)
	    die(3);
	}

}

void hexdump(void *mem, size_t len)
{
    unsigned int i, j;
    
    for(i = 0; 
		i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); 
		i++)
    {
        /* print offset */
        if(i % HEXDUMP_COLS == 0)
                printf("0x%06x: ", i);

        /* print hex data */
        if(i < len)
                printf("%02x ", 0xFF & ((char*)mem)[i]);
        else /* end of block, just aligning for ASCII dump */
                printf("   ");
        
        /* print ASCII dump */
        if(i % HEXDUMP_COLS == (HEXDUMP_COLS - 1))
        {
            for(j = i - (HEXDUMP_COLS - 1); j <= i; j++)
            {
                if(j >= len) /* end of block, not really printing */
                        putchar(' ');
                else if(isprint(((char*)mem)[j])) /* printable char */
                        putchar(0xFF & ((char*)mem)[j]);        
                else /* other char */
                        putchar('.');
            }
            putchar('\n');
        }
    }
}

int read_at_address_pipe(void* address, void* buf, size_t len)
{
        int ret = 1;
        int pipes[2];

        if(pipe(pipes))
                return 1;

        if(write(pipes[1], address, len) != len)
                goto end;
        if(read(pipes[0], buf, len) != len)
                goto end;

        ret = 0;
end:
        // if(! ret){
                // printf("buf value:%p ",*(unsigned int *)buf);
        // }

        close(pipes[1]);
        close(pipes[0]);
        return ret;
}

int write_at_address_pipe(void* address, void* buf, size_t len)
{
        int ret = 1;
        int pipes[2];

        if(pipe(pipes))
                return 1;

        if(write(pipes[1], buf, len) != len)
                goto end;
        if(read(pipes[0], address, len) != len)
                goto end;

        ret = 0;
end:
        close(pipes[1]);
        close(pipes[0]);
        return ret;
}

void *get_kallsym_address(const char *symbol_name, char* symbol_type) 
{
    FILE *f = fopen("/proc/kallsyms", "r");
    char c, sym[128];
    void *addr = NULL;

    while(fscanf(f, "%p %c %s\n", &addr, &c, sym) > 0)
        if (!strcmp(sym, symbol_name)) {
            goto done;
        }
done:
    fclose(f);
    return addr;    
}

inline int writel_at_address_pipe(void* address, size_t val)
{
        return write_at_address_pipe(address, &val, sizeof(val));
}


#define KERNEL_START 0xffffffc000000000
inline int is_cpu_timer_valid(struct list_head *cpu_timer)
{
  if (cpu_timer->next != cpu_timer->prev) {
    return 0;
  }

  if ((unsigned long int)cpu_timer->next < KERNEL_START) {
    return 0;
  }

  return 1;
}


