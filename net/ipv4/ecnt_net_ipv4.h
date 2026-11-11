#ifndef _LINUX_ECNT_NET_IPV4_H
#define _LINUX_ECNT_NET_IPV4_H
#include <uapi/linux/in.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/icmp.h>
#include <ecnt_hook/ecnt_hook.h>
#include <linux/ecnt_vlan_bind.h>
#include "../ecnt_net.h"
#include <linux/foe_hook.h>
#include "../../include/uapi/linux/ecnt_in.h"

#if defined(TCSUPPORT_TSO_ENABLE)
#include <ecnt_hook/ecnt_hook_tso.h>
#endif 

#define IP_CMSG_PKTINFO		1
#define IP_CMSG_TTL			2
#define IP_CMSG_TOS			4
#define IP_CMSG_RECVOPTS	8
#define IP_CMSG_RETOPTS		16
#define IP_CMSG_PASSSEC		32
#define IP_CMSG_ORIGDSTADDR 64
#define IP_CMSG_SKB_MARK    128
#define IP_CMSG_VLAN_ID		256

static inline int ecnt_do_ip_setsockopt_inline_hook
(struct sock *sk, int level, struct inet_sock *inet,
int optname, char __user *optval, unsigned int optlen, int *err)
{
	int val = 0;

	switch ( optname )
	{
		case IP_SKB_MARK_FLAG:
		case IP_SKB_VLAN_ID_FLAG:
		case IP_SKB_MARK:
		case IP_SKB_VLAN_ID:
		case IP_SKB_PBIT:
			if (optlen >= sizeof(int))
			{
				if (get_user(val, (int __user *) optval))
					return ECNT_HOOK_ERROR;
			}
			else if (optlen >= sizeof(__u16))
			{
				__u16 u16val;
				if (get_user(u16val, (__u16 __user *) optval))
					return ECNT_HOOK_ERROR;
				val = (int) u16val;
			}
			else if (optlen >= sizeof(char))
			{
				unsigned char ucval;
				if (get_user(ucval, (unsigned char __user *) optval))
					return ECNT_HOOK_ERROR;
				val = (int) ucval;
			}
			break;
		default:
			break;
	}

	switch ( optname )
	{
		case IP_SKB_MARK_FLAG:
			if ( val )
				inet->cmsg_flags |=  IP_CMSG_SKB_MARK;
			else
				inet->cmsg_flags &= ~IP_CMSG_SKB_MARK;
			*err = 0;
			break;
		case IP_SKB_VLAN_ID_FLAG:
			if ( val )
				inet->cmsg_flags |=  IP_CMSG_VLAN_ID;
			else
				inet->cmsg_flags &= ~IP_CMSG_VLAN_ID;
			*err = 0;
			break;
		case IP_SKB_MARK:
			sk->sk_mark = val;
			*err = 0;
			break;
		case IP_SKB_VLAN_ID:
			sk->lVlanId = val;
			*err = 0;
			break;
		case IP_SKB_PBIT:	
			sk->lPbit = val;
			*err = 0;
			break;
		default:
			break;
	}

	return ECNT_CONTINUE;
}

static inline int ecnt_do_ip_getsockopt_inline_hook
(struct sock *sk, int level, struct inet_sock *inet,
int optname, char __user *optval, int __user *optlen, unsigned int flags)
{
	int val = 0, len = 0;

	if (get_user(len, optlen))
		return ECNT_HOOK_ERROR;
	if (len < 0)
		return ECNT_HOOK_ERROR;

	switch ( optname )
	{
		case IP_SKB_MARK_FLAG:
			val = (inet->cmsg_flags & IP_CMSG_SKB_MARK) != 0;
			break;
		case IP_SKB_VLAN_ID_FLAG:
			val = (inet->cmsg_flags & IP_CMSG_VLAN_ID) != 0;
			break;
		case IP_SKB_MARK:
			val = sk->sk_mark;
			break;
		case IP_SKB_VLAN_ID:
			val = sk->lVlanId;
			break;
		default:
			return ECNT_CONTINUE;
	}

	if (len < sizeof(u16) && len > 0 && val >= 0 && val <= 255) {
		unsigned char ucval = (unsigned char)val;
		len = 1;
		if (put_user(len, optlen))
			return ECNT_HOOK_ERROR;
		if (copy_to_user(optval, &ucval, 1))
			return ECNT_HOOK_ERROR;
	} else {
		len = min_t(unsigned int, sizeof(int), len);
		if (put_user(len, optlen))
			return ECNT_HOOK_ERROR;
		if (copy_to_user(optval, &val, len))
			return ECNT_HOOK_ERROR;
	}


	return ECNT_RETURN;
}

static inline void ip_cmsg_recv_skbmark
(struct msghdr *msg, struct sk_buff *skb)
{
	__u32 skb_mark = skb->mark;
	put_cmsg(msg, SOL_IP, IP_SKB_MARK_FLAG, sizeof(__u32), &skb_mark);
}
static inline void ip_cmsg_recv_vlanid
(struct msghdr *msg, struct sk_buff *skb)
{
#if defined(TCSUPPORT_CT_VLAN_BIND)
	__be16 lVlanId = VBIND_INVALID_VLANID;

	if (ROUTING_MODE_VLAN_PACKET == 
		(skb->vlan_tag_flag & ROUTING_MODE_VLAN_PACKET)
		&& (skb->vlan_tags[0] < VBIND_INVALID_VLANID) )
		lVlanId = skb->vlan_tags[0];

	put_cmsg(msg, SOL_IP, IP_SKB_VLAN_ID_FLAG, sizeof(__u16), &lVlanId);
#endif
}

static inline void ecnt_ip_cmsg_recv_inline_hook
(struct msghdr *msg, struct sk_buff *skb, int flags)
{
	if ( (flags>>=1) == 0 )
		return;
	if ( flags & 1 )
		ip_cmsg_recv_skbmark(msg, skb);

	if ( (flags>>=1) == 0 )
		return;
	if ( flags & 1 )
		ip_cmsg_recv_vlanid(msg, skb);

	return;
}

static inline int ecnt_udp_send_skb_inline_hook
(struct inet_sock *inet, struct sock *sk, struct sk_buff *skb)
{
	if ( !inet || !sk || !skb )
		return ECNT_CONTINUE;

#if defined(TCSUPPORT_CT_VLAN_BIND)
	ecnt_dns_vlanid_store(inet, sk, skb);
#endif

	return ECNT_CONTINUE;
}

static inline int ecnt_tcp_recvmsg_inline_hook
(struct sock *sk, struct sk_buff *skb)
{
	if ( !sk || !skb )
		return ECNT_CONTINUE;

	ecnt_skbmark_to_sockmark_copy(sk, skb);

	return ECNT_CONTINUE;
}


static inline int ecnt_udp_recvmsg_inline_hook
(struct sock *sk, struct sk_buff *skb)
{
	if ( !sk || !skb )
		return ECNT_CONTINUE;

	ecnt_skbmark_to_sockmark_copy(sk, skb);

	return ECNT_CONTINUE;
}

static inline int ecnt_tcp_v4_rcv_inline_hook
(struct sock *sk, struct sk_buff *skb, struct net *net,
struct iphdr *iph, struct tcphdr *th)
{
#if defined(TCSUPPORT_CT)
	static uint32_t oldstamp = 0,newstamp = 0;
#endif

	if (!sk)
	{
#if defined(TCSUPPORT_CT)
		if(nf_conntrack_ftp_port == ntohs(th->dest)
			&& !strstr(skb->dev->name, "br0")
		  )
		{
			newstamp = jiffies;
			if(jiffies_to_usecs(newstamp - oldstamp) >= 5*USEC_PER_SEC)
				printk(KERN_INFO "TCSysLog FTP service is not open,"
				" reject incoming connection from %d.%d.%d.%d\n",
				((unsigned char *)&iph->saddr)[0],((unsigned char *)&iph->saddr)[1],
				((unsigned char *)&iph->saddr)[2],((unsigned char *)&iph->saddr)[3]);
			oldstamp = newstamp;
		}
		if ( nf_conntrack_portscan_enable )
		{
			if (!xfrm4_policy_check(NULL, XFRM_POLICY_IN, skb))
				return ECNT_RETURN_DROP;

			if (skb->len < (th->doff << 2) || tcp_checksum_complete(skb))
			{
				TCP_INC_STATS_BH(net, TCP_MIB_CSUMERRORS);
				TCP_INC_STATS_BH(net, TCP_MIB_INERRS);
			}	

			return ECNT_RETURN_DROP;			
		}
#endif
	}

        if(ra_sw_nat_local_in_tx)
            ra_sw_nat_local_in_tx(skb, ntohs(th->dest));

	return ECNT_CONTINUE;
}

static inline int ecnt_udp_v4_rcv_inline_hook
(struct sk_buff *skb, struct udphdr *uh)
{
    if (ra_sw_nat_local_in_tx 
        && (ECNT_RETURN_DROP == ra_sw_nat_local_in_tx(skb, ntohs(uh->dest))))
    {
        return ECNT_RETURN_DROP;
    }

    return ECNT_CONTINUE;
}

static inline int ecnt_icmp_send_inline_hook
(struct sk_buff *skb_in, int type, int code, __be32 info)
{

#if defined(TCSUPPORT_CT)
	if ( nf_conntrack_portscan_enable
		&& ICMP_DEST_UNREACH == type
		&& ICMP_PORT_UNREACH == code )
	{
		return ECNT_RETURN;
	}
#endif

	return ECNT_CONTINUE;
}


static inline int ecnt_arp_xmit_inline_hook
(struct sk_buff *skb)
{
#if defined(TCSUPPORT_CT_QOS)
	ecnt_set_qoshigh_hook(skb);
#endif

	return ECNT_CONTINUE;
}

#if defined(TCSUPPORT_TSO_ENABLE)
/* if match the rule, then set the tso mark.  */
static inline int ecnt_tcp_v4_send_check_inline_hook(struct sk_buff *skb, 
					__be32 saddr, __be32 daddr)
{
	tsoRuleEntry_v4_t entry;
	struct tcphdr *th;

	th = tcp_hdr(skb);
	entry.dport = ntohs(th->dest);
	entry.sport = ntohs(th->source);
	entry.daddr_v4 = daddr;
	entry.saddr_v4 = saddr;
	
	if(TSO_SET_SKB_MARK_V4(&entry) == 0){
		skb->tso_mark |= TSO_ENABLE_MARK;
	}
	else{
		skb->tso_mark &= (~TSO_ENABLE_MARK);
	}
	return ECNT_CONTINUE;
}
#endif

static inline void ecnt_ipmr_cache_report_inline_hook(struct sock *sk, 
struct sk_buff *skb, struct sk_buff *pkt)
{
	skb->dev = pkt->dev;
	skb->mark = pkt->mark;
	skb->skb_iif = pkt->skb_iif;	 
	ipv4_pktinfo_prepare(sk, skb);

	return;
}

#if defined(TCSUPPORT_TEST_SAMBA_SHORTCUT)
extern int SmbdTxSpeedOn;
extern int SmbdTxSpeedCnt0;
static inline int sambaTxShortCut(struct sk_buff *skb)
{
	struct iphdr *iph = NULL;
	
	skb->protocol = htons(ETH_P_IP);
	/*add layer3 header*/	
	skb_push(skb, sizeof(struct iphdr));
	skb_reset_network_header(skb);
	memcpy(skb->data, skb->sk->sk_smbd_info.smbd_ip_header, sizeof(struct iphdr));
	iph = ip_hdr(skb);
	iph->tot_len = htons(skb->len);
	/*add layer2 header*/	
	skb_push(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	memcpy(skb->data, skb->sk->sk_smbd_info.smbd_mac_header, ETH_HLEN);	

	skb->dev = (struct net_device *)(skb->sk->sk_smbd_info.smbd_outDev);
	return dev_queue_xmit(skb);
}
#endif
static inline int ecnt_tcp_transmit_skb_inline_hook(struct sk_buff *skb)
{

#if defined(TCSUPPORT_TEST_SAMBA_SHORTCUT)
	if(SmbdTxSpeedOn && skb->sk && skb->sk->sk_smbd_info.smbd_sk)
	{
		/* this samba flow has speed up, has learn mac & IP */
		if(skb->sk->sk_smbd_info.smbd_speed){
			if(skb->sk->sk_smbd_info.smbd_outDev == NULL){
				printk("samba tx shortcut: NULL dev \n");
				return ECNT_HOOK_ERROR;
			}
			
			SmbdTxSpeedCnt0++;
			skb->smbd_on_speed = 1;
			return sambaTxShortCut(skb);
		}else{
			skb->smbd_on_speed = 0;
		}
	}
#endif
	
	return ECNT_HOOK_ERROR; 
}

#endif

