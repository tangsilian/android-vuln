#ifndef ONE_IGMP_H 
#define ONE_IGMP_H

#define __rcu

struct callback_head {
    struct callback_head *next;
    void (*func)(struct callback_head *head);
};
#define rcu_head callback_head

struct ip_sf_socklist {
    unsigned int        sl_max;
    unsigned int        sl_count;
    struct rcu_head     rcu;
    __be32          sl_addr[0];
};

struct ip_mc_socklist {
    struct ip_mc_socklist __rcu *next_rcu;
    struct ip_mreqn     multi;
    unsigned int        sfmode;     /* MCAST_{INCLUDE,EXCLUDE} */
    struct ip_sf_socklist __rcu *sflist;
    struct rcu_head     rcu;
};
#endif // ONE_IGMP_H
