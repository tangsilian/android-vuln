#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define OOM_DISABLE             (-17)

int
protect_from_oom_killer(void)
{
  int fd;
  char buf[16];
  int ret;

  fd = open("/proc/self/oom_adj", O_WRONLY);
  if (fd == -1) {
    return -1;
  }

  sprintf(buf, "%d\n", OOM_DISABLE);

  ret = write(fd, buf, strlen(buf));
  if (ret == -1) {
    close(fd);
    return -1;
  }

  ret = close(fd);
  if (ret == -1) {
    return -1;
  }

  return 0;
}
