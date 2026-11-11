#ifndef _LINUX_ECNT_IN_H
#define _LINUX_ECNT_IN_H

/*
#define IP_MINTTL       21
#define IP_NODEFRAG     22
*/
#define	IP_SKB_MARK_FLAG	23
#define	IP_SKB_VLAN_ID_FLAG	24


/*
#define IP_MULTICAST_ALL		49
#define IP_UNICAST_IF			50
*/
#define	IP_SKB_MARK			51
#define	IP_SKB_VLAN_ID		52

#define IP_SKB_PBIT 		54


/* interface type */
#define 	IF_TYPE_WAN_ROUTE			(1<<0)
#define		IF_TYPE_WAN_BRIDE			(1<<1)
#define		IF_TYPE_LAN					(1<<2)
#define		IF_TYPE_INTERNET			(1<<3)
#define		IF_TYPE_OTHER				(1<<4)
#define 	IF_TYPE_HAS_REGISTER		(1<<5)
#define 	IF_TYPE_LAN_BIND_INTERNET	(1<<6)
#define 	IF_TYPE_OTHER_WAN_BRIDE		(IF_TYPE_WAN_BRIDE | IF_TYPE_OTHER)

#define 	MAX_PVC_NUM 			8
#define		MAX_SMUX_NUM			8

#if defined(TCSUPPORT_CT_VLAN_BIND)
#define 	VBIND_ENTRY_ARRAY_PATH "tc3162/vbind_entry_array"
#define		VBIND_INVALID_VLANID	4096
#define		VBIND_DNSPORT			53
#endif

#if defined(TCSUPPORT_TEST_SAMBA_SHORTCUT)
#define 	SAMBA_SHORTCUT_PATH "tc3162/samba_shortcut"
#endif

#endif /* _LINUX_ECNT_IN_H */
