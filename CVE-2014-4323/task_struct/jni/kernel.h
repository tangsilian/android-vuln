#ifndef KERNEL_H_
#define KERNEL_H_

typedef int  (*fnPrintk)(char*,...);

#define _LINUX_CAPABILITY_U32S_3     2
#define _KERNEL_CAPABILITY_U32S    _LINUX_CAPABILITY_U32S_3

extern int file_caps_enabled;

typedef struct kernel_cap_struct {
        __u32 cap[_KERNEL_CAPABILITY_U32S];
} kernel_cap_t;

typedef struct tmycred {
        int        usage;
        uid_t           uid;            /* real UID of the task */
        gid_t           gid;            /* real GID of the task */
        uid_t           suid;           /* saved UID of the task */
        gid_t           sgid;           /* saved GID of the task */
        uid_t           euid;           /* effective UID of the task */
        gid_t           egid;           /* effective GID of the task */
        uid_t           fsuid;          /* UID for VFS ops */
        gid_t           fsgid;          /* GID for VFS ops */
        unsigned        securebits;     /* SUID-less security management */
        kernel_cap_t    cap_inheritable; /* caps our children can inherit */
        kernel_cap_t    cap_permitted;  /* caps we're permitted */
        kernel_cap_t    cap_effective;  /* caps we can actually use */
        kernel_cap_t    cap_bset;       /* capability bounding set */


        void            *security;      /* subjective LSM security */


}mycred;

struct task_security_struct {
        int osid;               /* SID prior to last execve */
        int sid;                /* current SID */
        int exec_sid;           /* exec SID */
        int create_sid;         /* fscreate SID */
        int keycreate_sid;      /* keycreate SID */
        int sockcreate_sid;     /* fscreate SID */
};

#define SECURITY_NAME_MAX	10
struct security_operations {
	char name[SECURITY_NAME_MAX + 1];

	int (*binder_set_context_mgr);
	int (*binder_transaction);
	int (*binder_transfer_binder);
	int (*binder_transfer_file);

	int (*ptrace_access_check) ;
	int (*ptrace_traceme) ;
	int (*capget) ;
	int (*capset);
	int (*capable);
	int (*quotactl) ;
	int (*quota_on) ;
	int (*syslog);
	int (*settime) ;
	int (*vm_enough_memory) ;

	int (*bprm_set_creds);
	int (*bprm_check_security);
	int (*bprm_secureexec) ;
	void (*bprm_committing_creds);
	void (*bprm_committed_creds) ;

	int (*sb_alloc_security) ;
	void (*sb_free_security);
	int (*sb_copy_data);
	int (*sb_remount);
	int (*sb_kern_mount) ;
	int (*sb_show_options) ;
	int (*sb_statfs) ;
	int (*sb_mount);
	int (*sb_umount) ;
	int (*sb_pivotroot);
	int (*sb_set_mnt_opts) ;
	void (*sb_clone_mnt_opts);
	int (*sb_parse_opts_str) ;

#ifdef CONFIG_SECURITY_PATH
	int (*path_unlink) (struct path *dir, struct dentry *dentry);
	int (*path_mkdir) (struct path *dir, struct dentry *dentry, umode_t mode);
	int (*path_rmdir) (struct path *dir, struct dentry *dentry);
	int (*path_mknod) (struct path *dir, struct dentry *dentry, umode_t mode,
			   unsigned int dev);
	int (*path_truncate) (struct path *path);
	int (*path_symlink) (struct path *dir, struct dentry *dentry,
			     const char *old_name);
	int (*path_link) (struct dentry *old_dentry, struct path *new_dir,
			  struct dentry *new_dentry);
	int (*path_rename) (struct path *old_dir, struct dentry *old_dentry,
			    struct path *new_dir, struct dentry *new_dentry);
	int (*path_chmod) (struct path *path, umode_t mode);
	int (*path_chown) (struct path *path, uid_t uid, gid_t gid);
	int (*path_chroot) (struct path *path);
#endif

	int (*inode_alloc_security);
	void (*inode_free_security) ;
	int (*inode_init_security);
	int (*inode_create) ;
	int (*inode_link) ;
	int (*inode_unlink);
	int (*inode_symlink);
	int (*inode_mkdir) ;
	int (*inode_rmdir);
	int (*inode_mknod);
	int (*inode_rename);
	int (*inode_readlink) ;
	int (*inode_follow_link);
	int (*inode_permission);
	int (*inode_setattr)	;
	int (*inode_getattr);
	int (*inode_setxattr);
	void (*inode_post_setxattr);
	int (*inode_getxattr) ;
	int (*inode_listxattr) ;
	int (*inode_removexattr);
	int (*inode_need_killpriv);
	int (*inode_killpriv) ;
	int (*inode_getsecurity) ;
	int (*inode_setsecurity) ;
	int (*inode_listsecurity);
	void (*inode_getsecid);

	int (*file_permission) ;
	int (*file_alloc_security);
	void (*file_free_security);
	int (*file_ioctl);

	int (*file_mmap) ;
	int (*file_mprotect) ;
	int (*file_lock);
	int (*file_fcntl) ;
	int (*file_set_fowner);
	int (*file_send_sigiotask) ;
	int (*file_receive);
	int (*dentry_open) ;

	int (*task_create);
	void (*task_free) ;
	int (*cred_alloc_blank);
	void (*cred_free) ;
	int (*cred_prepare);
	void (*cred_transfer);
	int (*kernel_act_as);
	int (*kernel_create_files_as);
	int (*kernel_module_request);
	int (*task_fix_setuid) ;
	int (*task_setpgid);
	int (*task_getpgid);
	int (*task_getsid) ;
	void (*task_getsecid);
	int (*task_setnice) ;
	int (*task_setioprio);
	int (*task_getioprio);
	int (*task_setrlimit);
	int (*task_setscheduler);
	int (*task_getscheduler);
	int (*task_movememory);
	int (*task_kill);
	int (*task_wait);
	int (*task_prctl);
	void (*task_to_inode);

	int (*ipc_permission);
	void (*ipc_getsecid);

	int (*msg_msg_alloc_security) ;
	void (*msg_msg_free_security);

	int (*msg_queue_alloc_security) ;
	void (*msg_queue_free_security);
	int (*msg_queue_associate) ;
	int (*msg_queue_msgctl);
	int (*msg_queue_msgsnd);
	int (*msg_queue_msgrcv) ;

	int (*shm_alloc_security) ;
	void (*shm_free_security);
	int (*shm_associate) ;
	int (*shm_shmctl);
	int (*shm_shmat) ;

	int (*sem_alloc_security);
	void (*sem_free_security);
	int (*sem_associate);
	int (*sem_semctlpolicydb) ;
	int (*sem_semop) ;

	int (*netlink_send) ;

	void (*d_instantiate) ;

	int (*getprocattr) ;
	int (*setprocattr) ;
	int (*secid_to_secctx) ;
	int (*secctx_to_secid);
	void (*release_secctx) ;

	int (*inode_notifysecctx);
	int (*inode_setsecctx);
	int (*inode_getsecctx);
#define CONFIG_SECURITY_NETWORK
#ifdef CONFIG_SECURITY_NETWORK
	int (*unix_stream_connect) ;
	int (*unix_may_send);

	int (*socket_create);
	int (*socket_post_create) ;
	int (*socket_bind);
	int (*socket_connect);
	int (*socket_listen) ;
	int (*socket_accept) ;
	int (*socket_sendmsg);
	int (*socket_recvmsg);
	int (*socket_getsockname);
	int (*socket_getpeername);
	int (*socket_getsockopt);
	int (*socket_setsockopt) ;
	int (*socket_shutdown);
	int (*socket_sock_rcv_skb);
	int (*socket_getpeersec_stream) ;
	int (*socket_getpeersec_dgram);
	int (*sk_alloc_security) ;
	void (*sk_free_security) ;
	void (*sk_clone_security) ;
	void (*sk_getsecid);
	void (*sock_graft) ;
	int (*inet_conn_request);
	void (*inet_csk_clone) ;
	void (*inet_conn_established) ;
	int (*secmark_relabel_packet) ;
	void (*secmark_refcount_inc) ;
	void (*secmark_refcount_dec);
	void (*req_classify_flow) ;
	int (*tun_dev_create);
	void (*tun_dev_post_create);
	int (*tun_dev_attach);
#endif	/* CONFIG_SECURITY_NETWORK */

#ifdef CONFIG_SECURITY_NETWORK_XFRM
	int (*xfrm_policy_alloc_security) (struct xfrm_sec_ctx **ctxp,
			struct xfrm_user_sec_ctx *sec_ctx);
	int (*xfrm_policy_clone_security) (struct xfrm_sec_ctx *old_ctx, struct xfrm_sec_ctx **new_ctx);
	void (*xfrm_policy_free_security) (struct xfrm_sec_ctx *ctx);
	int (*xfrm_policy_delete_security) (struct xfrm_sec_ctx *ctx);
	int (*xfrm_state_alloc_security) (struct xfrm_state *x,
		struct xfrm_user_sec_ctx *sec_ctx,
		u32 secid);
	void (*xfrm_state_free_security) (struct xfrm_state *x);
	int (*xfrm_state_delete_security) (struct xfrm_state *x);
	int (*xfrm_policy_lookup) (struct xfrm_sec_ctx *ctx, u32 fl_secid, u8 dir);
	int (*xfrm_state_pol_flow_match) (struct xfrm_state *x,
					  struct xfrm_policy *xp,
					  const struct flowi *fl);
	int (*xfrm_decode_session) (struct sk_buff *skb, u32 *secid, int ckall);
#endif	/* CONFIG_SECURITY_NETWORK_XFRM */

	/* key management security hooks */
#ifdef CONFIG_KEYS
	int (*key_alloc) (struct key *key, const struct cred *cred, unsigned long flags);
	void (*key_free) (struct key *key);
	int (*key_permission) (key_ref_t key_ref,
			       const struct cred *cred,
			       key_perm_t perm);
	int (*key_getsecurity)(struct key *key, char **_buffer);
#endif	/* CONFIG_KEYS */

#ifdef CONFIG_AUDIT
	int (*audit_rule_init) (u32 field, u32 op, char *rulestr, void **lsmrule);
	int (*audit_rule_known) (struct audit_krule *krule);
	int (*audit_rule_match) (u32 secid, u32 field, u32 op, void *lsmrule,
				 struct audit_context *actx);
	void (*audit_rule_free) (void *lsmrule);
#endif /* CONFIG_AUDIT */
};

#define PF_KTHREAD      0x00200000



/* symbol table array indices */
#define SYM_COMMONS 0
#define SYM_CLASSES 1
#define SYM_ROLES   2
#define SYM_TYPES   3
#define SYM_USERS   4
#define SYM_BOOLS   5
#define SYM_LEVELS  6
#define SYM_CATS    7
#define SYM_NUM     8

/* object context array indices */
#define OCON_ISID  0	/* initial SIDs */
#define OCON_FS    1	/* unlabeled file systems */
#define OCON_PORT  2	/* TCP and UDP port numbers */
#define OCON_NETIF 3	/* network interfaces */
#define OCON_NODE  4	/* nodes */
#define OCON_FSUSE 5	/* fs_use */
#define OCON_NODE6 6	/* IPv6 nodes */
#define OCON_NUM   7
struct symtab {
	int *table;	/* hash table (keyed on a string) */
	int nprim;		/* number of primary names in table */
};
struct avtab {
	int *htable;
	int nel;	/* number of elements */
	int nslot;      /* number of hash slots */
	short mask;       /* mask to compute hash func */

};

struct ebitmap {
	int *node;	/* first node in the bitmap */
	int highbit;	/* highest position in the total bitmap */
};


struct policydb {
	int mls_enabled;

	/* symbol tables */
	struct symtab symtab[SYM_NUM];
#define p_commons symtab[SYM_COMMONS]
#define p_classes symtab[SYM_CLASSES]
#define p_roles symtab[SYM_ROLES]
#define p_types symtab[SYM_TYPES]
#define p_users symtab[SYM_USERS]
#define p_bools symtab[SYM_BOOLS]
#define p_levels symtab[SYM_LEVELS]
#define p_cats symtab[SYM_CATS]

	/* symbol names indexed by (value - 1) */
	int *sym_val_to_name[SYM_NUM];

	/* class, role, and user attributes indexed by (value - 1) */
	int*class_val_to_struct;
	int*role_val_to_struct;
	int*user_val_to_struct;
	int *type_val_to_struct_array;

	/* type enforcement access vectors and transitions */
	struct avtab te_avtab;

	/* role transitions */
	int *role_tr;

	/* file transitions with the last path component */
	/* quickly exclude lookups when parent ttype has no rules */
	struct ebitmap filename_trans_ttypes;
	/* actual set of filename_trans rules */
	int *filename_trans;

	/* bools indexed by (value - 1) */
	int *bool_val_to_struct;
	/* type enforcement conditional access vectors and transitions */
	struct avtab te_cond_avtab;
	/* linked list indexing te_cond_avtab by conditional */
	int *cond_list;

	/* role allows */
	int *role_allow;

	/* security contexts of initial SIDs, unlabeled file systems,
	   TCP or UDP port numbers, network interfaces and nodes */
	int *ocontexts[OCON_NUM];

	/* security contexts for files in filesystems that cannot support
	   a persistent label mapping or use another
	   fixed labeling behavior. */
	int *genfs;

	/* range transitions table (range_trans_key -> mls_range) */
	int *range_tr;

	/* type -> attribute reverse mapping */
	int *type_attr_map_array;

	struct ebitmap policycaps;

	struct ebitmap permissive_map;

	/* length of this policy when it was loaded */
	size_t len;

	unsigned int policyvers;

	unsigned int reject_unknown : 1;
	unsigned int allow_unknown : 1;

	short process_class;
	int process_trans_perms;
};

struct mls_level {
	int sens;		/* sensitivity */
	struct ebitmap cat;	/* category set */
};

struct mls_range {
	struct mls_level level[2]; /* low == level[0], high == level[1] */
};

struct context {
	int user;
	int role;
	int type;
	int len;        /* length of string in bytes */
	struct mls_range range;
	char *str;	/* string representation if context cannot be mapped. */
};
#endif /* NAKE_H_ */
