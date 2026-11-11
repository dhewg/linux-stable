#ifndef __FOE_HOOK_H
#define __FOE_HOOK_H
#include <uapi/linux/foe_hook.h>

#define FOE_MAGIC_PCI		    0x7273
#define FOE_MAGIC_WLAN		    0x7274
#define FOE_MAGIC_GE		    0x7275
#define FOE_MAGIC_PPE		    0x7276
#define FOE_MAGIC_ATM		    0x7277
#define FOE_MAGIC_WLAN_7615	    0x7615

#ifdef TCSUPPORT_MT7510_FE
#define FOE_MAGIC_PTM		    0x7278
#define FOE_MAGIC_EPON		    0x7279
#define FOE_MAGIC_GPON		    0x727a
//#define FOE_MAGIC_CRYPTO	    0x727b

#define FOE_MAGIC_CRYPTO_E_1	    0x727b
#define FOE_MAGIC_CRYPTO_D_1	    0x727c
#define FOE_MAGIC_CRYPTO_E_2	    0x727d
#define FOE_MAGIC_CRYPTO_D_2	    0x727e
#define FOE_MAGIC_OFFLOAD	    0x727f
#define FOE_MAGIC_PTM_LAN		    0x7280
#endif

#define	FOE_MAGIC_L2TP_VPN_UPSTREAM	0x7281
#define	FOE_MAGIC_L2TP_VPN_DOWNSTREAM	0x7282

#define FOE_MAGIC_LOCAL				0x7283
#define FOE_MAGIC_XSI				0x7284

#define	FOE_MAGIC_GRE_UP_1	    0x7285
#define	FOE_MAGIC_GRE_UP_2	    0x7286
#define	FOE_MAGIC_GRE_DOWN_1	0x7287
#define	FOE_MAGIC_GRE_DOWN_2	0x7288

#define	FOE_MAGIC_SPEED_TEST_UPSTREAM	0x7289

#define	FOE_MAGIC_VXLAN_UP_1	0x728a
#define	FOE_MAGIC_VXLAN_UP_2	0x728b
#define	FOE_MAGIC_VXLAN_DOWN_1	0x728c
#define	FOE_MAGIC_VXLAN_DOWN_2	0x728d

#define FOE_MAGIC_ASYM_UPSTREAM 0x728e
#define FOE_MAGIC_ASYM_DOWNSTREAM 0x728f
#define	FOE_MAGIC_PTM_CIRPIR	0X7290

#define	FOE_MAGIC_VXLAN_UP_FRAG	0x7291

#define FOE_MAGIC_LOCAL_MCAST	0x7292

#define FOE_MAGIC_MAP_T_DOWN	0x7293
#define FOE_MAGIC_MAP_T_UP 		0x7294
#define FOE_MAGIC_MAP_T_DOWN_2	0x7295
#define FOE_MAGIC_MAP_T_UP_2	0x7296

#define	L2TP_VPN_PPP_NAME	"ppp100"
#define	HWNAT_PKT_ERROR		0
#define	HWNAT_PKT_UPSTREAM	1
#define	HWNAT_PKT_DOWNSTREAM	2

#define HWNAT_IPSEC_LEARING 0
#define HWNAT_IPSEC_SPEED 1
#define HWNAT_IPSEC_ROLLBACK 2

#define IPSEC_SKB_CB			47

#define FOE_OPE_GETENTRYNUM 0
#define FOE_OPE_CLEARENTRY  1

#define HWNAT_LAN_IF_MAXNUM	8
#define HWNAT_LAN_IF_BASE		0//0~7 is lan interface
#define HWNAT_WLAN_IF_MAXNUM	16 //16 is max wifi interface
#define HWNAT_WLAN_IF_BASE		16//16  is base
#define HWNAT_LAN_IF_MASK		(0xFFFF)
#define HWNAT_WLAN_IF_NUM		8 
#define HWNAT_WLAN_IF_I_NUM		8
#define HWNAT_RA_IF_MASK		(0xFF)
#define HWNAT_RAI_IF_MASK		(0xFF)
#define HWNAT_WLAN_IF_I_BASE		(HWNAT_WLAN_IF_BASE+HWNAT_WLAN_IF_NUM)
#define HWNAT_WLAN_IF_MASK		(HWNAT_RA_IF_MASK | (HWNAT_RAI_IF_MASK << (HWNAT_WLAN_IF_NUM)))


#define MULTICAST_SPEED_STATE_I 		3	//with lan and with wlan
#define MULTICAST_SPEED_STATE_II		1	//with lan and without wlan
#define MULTICAST_SPEED_STATE_III		2	//without lan and with wlan
#define MULTICAST_SPEED_STATE_IV   		0	//without lan and without wlan

#define LAN_STATE_I     1   //soc lan + external lan port
#define LAN_STATE_II    2   //only soc lan or only external lan port or both not

struct port_info {
    unsigned long int tsid:8;
    unsigned long int channel:5;
    unsigned long int nbq:5;
    unsigned long int :1;
    unsigned long int txq:4;
    unsigned long int atm_pppoa:1;
    unsigned long int atm_ipoa:1;
    unsigned long int atm_vc_mux:1;
    unsigned long int eth_macSTagEn:1;
	unsigned long int eth_is_wan:1;
    unsigned long int ds_to_qdma:1;
    unsigned long int ds_need_offload:1;
    unsigned long int force_high_priority_ring:1;
	unsigned long int txq_is_valid:1;
    unsigned long int stag:16;
    unsigned long int magic:16;
};

typedef union {
#ifdef TCSUPPORT_CPU_EN7580
struct {
#ifdef __BIG_ENDIAN
		unsigned int resv0		: 1 ;
		unsigned int mic_idx	: 1 ;
		unsigned int sp_tag		: 16 ;
		unsigned int ico		: 1;
		unsigned int uco		: 1;
		unsigned int tco		: 1;
		unsigned int tso		: 1;
		unsigned int fast		: 1 ;
		unsigned int oam		: 1 ;
		unsigned int channel	: 5 ;
		unsigned int queue		: 3 ;
#else
		unsigned int queue		: 3 ;
		unsigned int channel	: 5 ;
		unsigned int oam		: 1 ;
		unsigned int fast		: 1 ;
		unsigned int tso		: 1;
		unsigned int tco		: 1;
		unsigned int uco		: 1;
		unsigned int ico		: 1;
		unsigned int sp_tag		: 16 ;
		unsigned int mic_idx	: 1 ;
		unsigned int resv0		: 1 ;
#endif
	
#ifdef __BIG_ENDIAN
		unsigned int no_drop	: 1;	/*means not be dropped by QDMA*/
		unsigned int mtr_g		: 7;	/*0x7f means not use meter*/
		unsigned int fport		: 3;
		unsigned int nboq		: 5;
		unsigned int resv2		: 6;
		unsigned int act_grp	: 10;
#else
		unsigned int act_grp	: 10;
		unsigned int resv2		: 6;
		unsigned int nboq		: 5;
		unsigned int fport		: 3;
		unsigned int mtr_g		: 7;	/*0x7f means not use meter*/
		unsigned int no_drop	: 1;	/*means not be dropped by QDMA*/
#endif
	} raw ;
#else
	struct {
#ifdef __BIG_ENDIAN
		unsigned int resv				: 1 ;
		unsigned int tsid				: 5 ;
		unsigned int tse				: 1 ;
		unsigned int dei				: 1 ;
		unsigned int gem				: 12 ;
		unsigned int oam				: 1 ;
		unsigned int channel			: 8 ;
		unsigned int queue				: 3 ;	
#else
		unsigned int queue				: 3 ;	
		unsigned int channel			: 8 ;
		unsigned int oam				: 1 ;
		unsigned int gem				: 12 ;
		unsigned int dei				: 1 ;
		unsigned int tse				: 1 ;
		unsigned int tsid				: 5 ;
		unsigned int resv				: 1 ;
#endif /* __BIG_ENDIAN */

#ifdef __BIG_ENDIAN
		unsigned int ico				: 1 ;
		unsigned int uco				: 1 ;
		unsigned int tco				: 1 ;
		unsigned int tso				: 1 ;
		unsigned int pmap				: 6 ;
		unsigned int fport				: 3 ;
		unsigned int insv				: 1 ;
		unsigned int tpid				: 2 ;	
		unsigned int vid				: 16 ;	
#else
		unsigned int vid				: 16 ;	
		unsigned int tpid				: 2 ;	
		unsigned int insv				: 1 ;
		unsigned int fport				: 3 ;
		unsigned int pmap				: 6 ;
		unsigned int tso				: 1 ;
		unsigned int tco				: 1 ;
		unsigned int uco				: 1 ;
		unsigned int ico				: 1 ;
#endif /* __BIG_ENDIAN */
	} raw ;
#endif

	struct {
#ifdef __BIG_ENDIAN
		unsigned int mtr				: 1 ;
		unsigned int fport_ppe			: 3 ;
		unsigned int gem				: 16 ;
		unsigned int oam				: 1 ;
		unsigned int channel_ppe		: 5 ;
		unsigned int channel			:3 ;
		unsigned int queue				: 3 ;	
#else
		unsigned int queue				: 3 ;	
		unsigned int channel			:3 ;
		unsigned int channel_ppe		: 8 ;
		unsigned int oam				: 1 ;
		unsigned int gem				: 16 ;
		unsigned int fport_ppe			: 3 ;
		unsigned int mtr				: 1 ;
#endif /* __BIG_ENDIAN */

#ifdef __BIG_ENDIAN
		unsigned int ico				: 1 ;
		unsigned int uco				: 1 ;
		unsigned int tco				: 1 ;
		unsigned int tso				: 1 ;
		unsigned int mtr_index			: 6 ;
		unsigned int fport				: 3 ;
		unsigned int insv				: 1 ;
		unsigned int tpid				: 2 ;	
		unsigned int vid				: 16 ;	
#else
		unsigned int vid				: 16 ;	
		unsigned int tpid				: 2 ;	
		unsigned int insv				: 1 ;
		unsigned int fport				: 3 ;
		unsigned int mtr_index			: 6 ;
		unsigned int tso				: 1 ;
		unsigned int tco				: 1 ;
		unsigned int uco				: 1 ;
		unsigned int ico				: 1 ;
#endif /* __BIG_ENDIAN */
	} raw1 ;/*tx msg format1 for cpu path ratelimit by ppe meter in EN7526C*/
	
	unsigned int word[2] ;
}FETxMsg_T ;


/*****************************
 * FRAME ENGINE REGISTERS OFFSET *
 *****************************/
#define FE_GLO_CFG_OFF          (0x0000)
#define CDMP_VLAN_CT_OFF		(0x0400)
#define CDM_VLAN_GE_OFF         (0x1400)
#define GDM2_FWD_CFG_OFF		(0x1500)
#define GDM2_MIB_CLR_OFF		(0x1520)
#define GDM2_LEN_CFG_OFF		(0x1524)
#define GDM2_CHN_EN_OFF			(0x152c)
#define GDM2_TX_GET_CNT_OFF		(0x1600)
#define GDM2_TX_OK_CNT_OFF		(0x1604)
#define GDM2_TX_DROP_CNT_OFF	(0x1608)
#define GDM2_TX_OK_BYTE_CNT_OFF	(0x160c)
#define GDM2_RX_OK_CNT_OFF		(0x1650)
#define GDM2_RX_OVER_DROP_CNT_OFF	(0x1654)
#define GDM2_RX_ERROR_DROP_CNT_OFF	(0x1658)
#define GDM2_RX_OK_BYTE_CNT_OFF		(0x165c)
#define GDM2_RX_ETH_CRCE_CNT_OFF	(0x1674)
#define GDM2_RX_ETH_RUNT_CNT_OFF	(0x1680)
#define GDM2_RX_ETH_LONG_CNT_OFF	(0x1684)


struct sk_buff;
struct net_device;
struct net_device_stats;

extern int (*ra_sw_nat_hook_rx_set_l2lu) (struct sk_buff * skb, unsigned int direction, int PpeIndex);
extern int (*ra_sw_nat_hook_rx) (struct sk_buff * skb);
extern int (*ra_sw_nat_hook_wifi_tx) (struct sk_buff * skb, unsigned int rx_len);
extern int (*ra_sw_nat_to_wifi_fast_tx) (struct sk_buff * skb);
extern int (*ra_sw_nat_mcst_offload)(struct sk_buff *skb, int *dp);
extern int (*ra_sw_nat_ds_offload)(struct sk_buff *skb, int *dp);
extern int (*ra_sw_nat_hook_update_dp)(int index, int dp);
extern int (*ra_sw_nat_hook_update_vlan)(int index,int outer_vlan,int inner_vlan);
extern int (*ra_sw_nat_local_in_tx) (struct sk_buff * skb,unsigned short port);

extern int (*ra_sw_nat_hook_save_rxinfo)(struct sk_buff *skb);
extern int (*ra_sw_nat_hook_restore_rxinfo)(struct sk_buff *skb);
extern int (*ra_sw_nat_hook_save_txinfo)(struct sk_buff *skb);
extern int (*ra_sw_nat_hook_restore_txinfo)(struct sk_buff *skb);
extern int (*ra_sw_nat_hook_save_gre_txinfo)(struct sk_buff *skb);
extern int (*ra_sw_nat_hook_restore_gre_txinfo)(struct sk_buff *skb);
extern int (*ra_sw_nat_hook_is_gre_offload_pkt)(struct sk_buff *skb);
extern int (*ra_sw_nat_hook_save_vxlan_txinfo)(struct sk_buff *skb);
extern int (*ra_sw_nat_hook_restore_vxlan_txinfo)(struct sk_buff *skb);
extern int (*ra_sw_nat_hook_is_vxlan_offload_pkt)(struct sk_buff *skb);
extern int (*ra_sw_nat_hook_is_hwnat_pkt)(struct sk_buff *skb);
extern int (*ra_sw_nat_hook_sendto_ppe)(struct sk_buff *skb);
extern int (*ra_sw_nat_hook_set_l2tp_dev)(struct net_device *dev);
extern struct net_device* (*ra_sw_nat_hook_read_l2tp_dev)(void);
extern int (*ra_sw_nat_rtsp_offload_restore) (struct sk_buff * skb, int calc_sum);
extern int (*ra_sw_nat_rtsp_data_handle) (struct sk_buff * skb, char *rb_ptr, unsigned int datalen);
extern void (*ra_sw_nat_set_wan_acntid_hook) (struct sk_buff *skb, unsigned char wan_index, unsigned char dir);
extern void (*ra_sw_nat_clear_wan_acntid_hook)(unsigned char wan_index);
extern void (*ra_sw_nat_get_wan_acntid_counter_hook)(unsigned char wan_index, struct net_device_stats *storage);
extern void (*ra_sw_nat_set_mac_hook) (struct sk_buff *skb, unsigned char *mac);

#ifdef TCSUPPORT_MT7510_FE
extern int (*ra_sw_nat_hook_tx) (struct sk_buff * skb, struct port_info * pinfo, int magic);
#else
extern int (*ra_sw_nat_hook_tx) (struct sk_buff * skb, int gmac_no);
#endif
extern int (*ra_hit_bind_force_to_cpu) (struct sk_buff * skb);
extern int (*ra_sw_nat_hook_free) (struct sk_buff * skb);
extern int (*ra_sw_nat_hook_rxinfo) (struct sk_buff * skb, int magic, char *data, int data_length);
extern int (*ra_sw_nat_hook_txq) (struct sk_buff * skb, int txq);
extern int (*ra_sw_nat_hook_magic) (struct sk_buff * skb, int magic);
extern int (*ra_sw_nat_hook_set_magic) (struct sk_buff * skb, int magic);
extern int (*ra_sw_nat_hook_xfer) (struct sk_buff *skb, const struct sk_buff *prev_p);
extern int (*ra_sw_nat_hook_foeentry) (void * inputvalue,int operation);
extern int (*ra_sw_nat_hook_is_entry_valid) (int foe_entry_idx, int ring_idx);
extern int (*ra_sw_nat_hook_is_alive_pkt)(unsigned int crsn);
#if defined(TCSUPPORT_CPU_MT7520) || defined(TCSUPPORT_CPU_EN7512)
extern int (*MT7530LanPortMap2Switch_hook)(int port); 
#endif

#ifdef TCSUPPORT_RA_HWNAT_ENHANCE_HOOK
extern int (*ra_sw_nat_hook_drop_packet) (struct sk_buff * skb);
extern int (*ra_sw_nat_hook_clean_table) (void);
extern int (*ra_sw_nat_hook_clean_multicast_entry) (void);
#endif

#ifdef TCSUPPORT_MT7510_FE
extern void (*restore_offload_info_hook)(struct sk_buff *skb, struct port_info *pinfo, int magic);
#endif

extern int (*ra_sw_nat_hook_cpu_meter)(struct sk_buff* skb,FETxMsg_T* txMsg,struct port_info* pinfo,unsigned char dir,unsigned short mtrIndex);
#endif
