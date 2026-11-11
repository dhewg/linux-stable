#ifndef _LINUX_ECNT_NET_IPV4_H
#define _LINUX_ECNT_NET_IPV4_H
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <uapi/linux/in6.h>
#include <ecnt_hook/ecnt_hook.h>
#include "../ecnt_net.h"
#include <linux/ecnt_vlan_bind.h>
#include <net/tcp.h>
#include <net/addrconf.h>

#ifdef TCSUPPORT_IPV6_ENHANCEMENT
static void addrconf_add_linklocal(struct inet6_dev *idev, const struct in6_addr *addr);
static int ipv6_generate_eui64(u8 *eui, struct net_device *dev);
#endif

#if defined(TCSUPPORT_CT_WAN_CHILD_PREFIX)
#define PREFIX_ORIGN_DFT	0
#define PREFIX_ORIGN_SLLA	1
#define PREFIX_ORIGN_DHCP	2
#define PREFIX_ORIGN_STATIC	3
#define PREFIX_ORIGN_NONE	4

#define INET6_S16_ADDR_BYTES	8
#define MAX_PD_PREFIX 	64
#endif

#if defined(TCSUPPORT_CT)
#define MAX_PVC_NUM 8
#define isdigit(c)	('0' <= (c) && (c) <= '9')
static inline int skip_atoi(char *s)
{
	int i=0;

	while (isdigit(*s))
		i = i*10 + *(s++) - '0';
	return i;
}
#endif
#define IP_CMSG_SKB_MARK    128

static inline int ecnt_udp6_lib_rcv_inline_hook
( struct sk_buff *skb,struct udphdr *uh, int proto)
{
#if defined(TCSUPPORT_CT_PORTSLIMIT)
	if ( IPPROTO_UDP == proto )
	{
		if ( NULL != skb->dev &&
			( ('n' == skb->dev->name[0] && 'a' == skb->dev->name[1] && 's' == skb->dev->name[2])
			|| ('p' == skb->dev->name[0] && 'p' == skb->dev->name[1] && 'p' == skb->dev->name[2]))
			)
		{
			if ( 53 == uh->dest
				|| 547 == uh->dest
				|| 1900 == uh->dest )
				return ECNT_RETURN_DROP;
		}
	}
#endif

	return ECNT_CONTINUE;
}

static inline void ecnt_udpv6_recvmsg_inline_hook
(struct msghdr *msg, struct sk_buff *skb, struct inet_sock *inet, int is_udp4)
{
	if ( !is_udp4 && skb->protocol == htons(ETH_P_IPV6) )
	{
		if ( inet->cmsg_flags & IP_CMSG_SKB_MARK )
		{
			ip_cmsg_recv(msg, skb); 
		}
	}

	return;
}

static inline void ecnt_udpv6_sendmsg_inline_hook
(struct flowi6 *p_fl6, struct sock *sk)
{
#if defined(TCSUPPORT_CT)
	struct net_device *dev = NULL;
	char if_buf[10];
	int if_index = 0;
#endif

	if ( !p_fl6 )
		return;

#if defined(TCSUPPORT_CT)
	if ( !p_fl6->flowi6_oif )
	{
		p_fl6->flowi6_oif = sk->sk_bound_dev_if;
		if ( p_fl6->flowi6_oif )
		{
			dev = dev_get_by_index(sock_net(sk), sk->sk_bound_dev_if);
			if ( dev )
			{
				memset(if_buf, 0, sizeof(if_buf));
				
					if ( strlen(dev->name) > 3 )
					strlcpy(if_buf, dev->name + 3, sizeof(if_buf));
					if ( dev->name[0] == 'n' && strlen(if_buf) > 2 )
					{
						if_index = (if_buf[0] - '0') * MAX_PVC_NUM 
							+ (if_buf[2] - '0');
						sk->sk_mark &= (~0x7f0000);
						sk->sk_mark |= (if_index + 1) << 16;
					}
					else if ( dev->name[0] == 'p' )
					{
						if_index = skip_atoi(if_buf);
						sk->sk_mark &= (~0x7f0000);
						sk->sk_mark |= (if_index + 1) << 16;
					}
				
				dev_put(dev);
			}
		}
	}
#endif

	return;
}

static inline int ecnt_do_ipv6_setsockopt_inline_hook
(struct sock *sk, int level, struct net *net, int usrval,
int optname, char __user *optval, unsigned int optlen, int *err)
{
	int val = usrval;

	if ( optlen < sizeof(int) )
	{
		if (optlen >= sizeof(__u16))
		{
			__u16 u16val;
			if (get_user(u16val, (__u16 __user *) optval))
				return ECNT_HOOK_ERROR;
			val = (int) u16val;
		}
		else if ( optlen >= sizeof(char) )
		{
			unsigned char ucval;
		
			if ( get_user(ucval, (unsigned char __user *) optval) )
			{
				*err = -EFAULT;
				return ECNT_HOOK_ERROR;
			}
			val = (int) ucval;
		}
	}

	switch ( optname )
	{
		case IPV6_SKB_MARK:
			*err = -EINVAL;
			if ( optlen < sizeof(int) )
				break;
			sk->sk_mark = val;
			*err = 0;
			break;
		case IPV6_SKB_VLAN_ID:
			*err = -EINVAL;
			if ( optlen < sizeof(__be16) )
				break;
			sk->lVlanId = val;
			*err = 0;
			break;
		default:
			break;
	}

	return ECNT_CONTINUE;
}

static inline int ecnt_do_ipv6_getsockopt_inline_hook
(struct sock *sk, int level, int optname, int *val,
char __user *optval, int __user *optlen, unsigned int flags)
{
	int len = 0;

	switch ( optname )
	{
		case IPV6_SKB_VLAN_ID:
			*val = sk->lVlanId;;
			break;
		default:
			return ECNT_CONTINUE;
	}

	return ECNT_RETURN;
}

static inline int ecnt_udp_v6_push_pending_frames_inline_hook
(struct inet_sock *inet, struct sock *sk, struct sk_buff *skb)
{
	if ( !inet || !sk || !skb )
		return ECNT_CONTINUE;

#if defined(TCSUPPORT_CT_VLAN_BIND)
	ecnt_dns_vlanid_store(inet, sk, skb);
#endif

	return ECNT_CONTINUE;
}

static inline int ecnt_tcp_v6_rcv_inline_hook
(struct sock *sk, struct sk_buff *skb,
struct net *net, struct ipv6hdr *hdr, struct tcphdr *th)
{
	if ( !sk )
	{
#if defined(TCSUPPORT_CT)
		if ( nf_conntrack_portscan_enable )
		{
			if (!xfrm6_policy_check(NULL, XFRM_POLICY_IN, skb))
				return ECNT_RETURN_DROP;
			tcp_v6_fill_cb(skb, hdr, th);
			if (skb->len < (th->doff<<2) || tcp_checksum_complete(skb))
			{
				TCP_INC_STATS_BH(net, TCP_MIB_CSUMERRORS);
				TCP_INC_STATS_BH(net, TCP_MIB_INERRS);
			}

			return ECNT_RETURN_DROP;
		}
#endif
	}
	else
	{
#if defined(TCSUPPORT_CT)
#ifndef CONFIG_TP_IMAGE
		if ( NULL != skb->dev && 'b' != skb->dev->name[0] )
		{
			if ( htons(80) == th->dest)
				return ECNT_RETURN_DROP;
		}
#endif /* CONFIG_TP_IMAGE */
#endif
	}

	return ECNT_CONTINUE;
}

static inline int ecnt_icmpv6_send_inline_hook
(struct sk_buff *skb_in, int type, int code, __be32 info)
{

#if defined(TCSUPPORT_CT)
	if ( nf_conntrack_portscan_enable
		&& ICMPV6_DEST_UNREACH == type
		&& ICMPV6_PORT_UNREACH == code )
	{
		return ECNT_RETURN;
	}
#endif

	return ECNT_CONTINUE;
}

static inline int ecnt_ndisc_send_skb_inline_hook
(struct sk_buff *skb)
{
#if defined(TCSUPPORT_CT_QOS)
	ecnt_set_qoshigh_hook(skb);
#endif

	return ECNT_CONTINUE;
}

#endif

#ifdef TCSUPPORT_IPV6_ENHANCEMENT
static inline int is_wan_dev(struct net_device *dev)
{
	return (strstr(dev->name, "nas") != NULL 
#if defined(TCSUPPORT_FH_ENV) || defined(TCSUPPORT_IS_FH_PON)
		|| strstr(dev->name, "pon0.") != NULL	
#endif
#if defined(TCSUPPORT_CT_WAN_PTM)
		|| strstr(dev->name, "ptm") != NULL	
#endif
		|| strstr(dev->name, "ppp") != NULL);
}
#endif


static inline int ecnt_ndisc_router_discovery_if_inline_hook(struct inet6_dev *in6_dev)
{
#ifdef TCSUPPORT_IPV6_ENHANCEMENT	
		/*Enable WAN interface to receive RA for SLAAC mode*/
	if (!is_wan_dev(in6_dev->dev) || !in6_dev->cnf.accept_ra) 
		return ECNT_CONTINUE;
	else 
		return ECNT_RETURN_DROP;
#else
	if (!ipv6_accept_ra(in6_dev)) 
		return ECNT_CONTINUE;
	else 
		return ECNT_RETURN_DROP;
#endif
	
}


static inline int ecnt_ndisc_router_discovery_inline_hook
(struct sk_buff *skb,struct inet6_dev *in6_dev,struct ndisc_options ndopts, struct neighbour *neigh)
{
#if defined(TCSUPPORT_CT_WAN_CHILD_PREFIX)
	struct prefix_info *pinfo_ptr = NULL;
	u16 pinfo_size = 0;
		
	/*using TR069 IPv6Address.ChildPrefixBits defined to generate a new prefix*/
	if(in6_dev->cnf.accept_ra_pinfo && !ndopts.nd_opts_pi)
	{
		if((in6_dev->cnf.child_prefix_orign == PREFIX_ORIGN_SLLA)
			&& (in6_dev->cnf.parent_pd_prefix[0] != '\0')
			&& (in6_dev->cnf.child_prefix[0] != '\0')){
			pinfo_size = sizeof(struct prefix_info);
			pinfo_ptr = kmalloc( pinfo_size, GFP_ATOMIC);
			if(pinfo_ptr == NULL){
				printk("[%s]---kmalloc fail!,[%d] \n",__FUNCTION__, __LINE__);
				goto childprefix_end;
	
			}
			pinfo_ptr->type = ND_OPT_PREFIX_INFO;
			pinfo_ptr->length = pinfo_size; //no using
			pinfo_ptr->onlink = 1;
			pinfo_ptr->autoconf = 1;
			pinfo_ptr->reserved = 0;
			pinfo_ptr->valid = 172800; // 2 day
			pinfo_ptr->prefered = 86400; // 1 day
			pinfo_ptr->reserved2 = 0;
				
			if(generate_prefix(skb, pinfo_ptr) == 0){
				addrconf_prefix_rcv(skb->dev, (u8*)pinfo_ptr, pinfo_size,
					ndopts.nd_opts_src_lladdr != NULL);
			}
			if(pinfo_ptr != NULL){
				kfree(pinfo_ptr);
			}
		}
	}
	childprefix_end:
				//nothing
#endif

	
#ifdef TCSUPPORT_IPV6_ENHANCEMENT
	if(neigh){
			/*Add for outputing default gateway by RA*/
	sprintf(neigh->parms->dlf_route, NIP6_FMT, NIP6(ipv6_hdr(skb)->saddr));
	}

#endif
	return ECNT_CONTINUE;
}

static inline int ecnt_addrconf_prefix_rcv_inline_hook
(struct inet6_dev *in6_dev,struct prefix_info *pinfo,struct in6_addr addr)
{
#if defined(TCSUPPORT_CT_WAN_CHILD_PREFIX)
	/*record the ra prefix info */
	sprintf(in6_dev->cnf.slaac_prefix, NIP6_FMT"/%d", NIP6(pinfo->prefix), pinfo->prefix_len);
#endif

#ifdef TCSUPPORT_IPV6_ENHANCEMENT
	/*Add for outputing slaac address by RA*/
	sprintf(in6_dev->cnf.slaac_addr, NIP6_FMT" %d", NIP6(addr), pinfo->prefix_len);
#endif
	return ECNT_CONTINUE;
}

static inline int ecnt_addrconf_dad_complete_if_inline_hook(struct inet6_ifaddr *ifp)
{
#ifdef TCSUPPORT_IPV6_ENHANCEMENT
		/*Enable WAN interface to send RS for SLAAC mode*/
		if(is_wan_dev(ifp->idev->dev) )
			return ECNT_CONTINUE;
		else
			return ECNT_RETURN_DROP;
#else
		if(ipv6_accept_ra(ifp->idev))
			return ECNT_CONTINUE;
		else
			return ECNT_RETURN_DROP;
#endif

}
static inline int ecnt_addrconf_rs_timer_if_inline_hook(struct inet6_dev *idev)
{
#ifdef TCSUPPORT_IPV6_ENHANCEMENT
		/*Enable WAN interface to send RS for SLAAC mode*/
		if(!is_wan_dev(idev->dev))
			return ECNT_CONTINUE;
		else 
			return ECNT_RETURN_DROP;
#else
		if (!ipv6_accept_ra(idev))
			return ECNT_CONTINUE;
		else
			return ECNT_RETURN_DROP;
#endif

}

static inline int ecnt_addrconf_dev_config_if_inline_hook(struct net_device *dev, struct inet6_dev *idev)
{
#ifdef TCSUPPORT_IPV6_ENHANCEMENT
		struct in6_addr addr;
		//Disable lan device add linklocal address,except br0
			if(is_wan_dev(dev) || (strstr(dev->name, "br") != NULL)){
				memset(&addr, 0, sizeof(struct in6_addr));
				addr.s6_addr32[0] = htonl(0xFE800000);
#ifndef CONFIG_TP_IMAGE
				//set br0 local link address as fe80::1
				if(strstr(dev->name, "br") != NULL){
					addr.s6_addr[8] = 0;
					addr.s6_addr[9] = 0;	
					addr.s6_addr[10] = 0;
					addr.s6_addr[11] = 0;
					addr.s6_addr[12] = 0;
					addr.s6_addr[13] = 0;
					addr.s6_addr[14] = 0;
					addr.s6_addr[15] = 1;
					addrconf_add_linklocal(idev, &addr);
				}
				else
#endif /* CONFIG_TP_IMAGE */
				{
					if (ipv6_generate_eui64(addr.s6_addr + 8, dev) == 0)
						addrconf_add_linklocal(idev, &addr);
				}
			}
			return ECNT_RETURN_DROP;
#else
	return ECNT_CONTINUE;
#endif

}



