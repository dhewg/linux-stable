#ifndef _LINUX_ECNT_NETFILTER_IPV6_H
#define _LINUX_ECNT_NETFILTER_IPV6_H
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <ecnt_hook/ecnt_hook.h>
#include "../ecnt_net_ipv6.h"

static inline int ecnt_ip6t_mangle_out_inline_hook
(struct sk_buff *skb, const struct net_device *out)
{
#if defined(TCSUPPORT_CT)
	char if_buf[10];
	int if_index = 0;
#endif

	if ( !skb || !out )
		return ECNT_CONTINUE;

#if defined(TCSUPPORT_CT)
	memset(if_buf, 0, sizeof(if_buf));
	
		if ( strlen(out->name) > 3 )
		strlcpy(if_buf, out->name + 3,sizeof(if_buf));

		if ( out->name[0] == 'n' && strlen(if_buf) > 2 )
		{
			if_index = (if_buf[0] - '0') * MAX_PVC_NUM + (if_buf[2] - '0');
			skb->mark |= (if_index + 1) << 16;
		}
		else if (out->name[0] == 'p')
		{
			if_index = skip_atoi(if_buf);
			skb->mark |= (if_index + 1) << 16;
		}
	
#endif

	return ECNT_CONTINUE;
}


#endif

