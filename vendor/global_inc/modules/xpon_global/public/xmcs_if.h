/***************************************************************
Copyright Statement:

This software/firmware and related documentation (“EcoNet Software? 
are protected under relevant copyright laws. The information contained herein 
is confidential and proprietary to EcoNet (HK) Limited (“EcoNet? and/or 
its licensors. Without the prior written permission of EcoNet and/or its licensors, 
any reproduction, modification, use or disclosure of EcoNet Software, and 
information contained herein, in whole or in part, shall be strictly prohibited.

EcoNet (HK) Limited  EcoNet. ALL RIGHTS RESERVED.

BY OPENING OR USING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY 
ACKNOWLEDGES AND AGREES THAT THE SOFTWARE/FIRMWARE AND ITS 
DOCUMENTATIONS (“ECONET SOFTWARE? RECEIVED FROM ECONET 
AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON AN “AS IS?
BASIS ONLY. ECONET EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, 
WHETHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, 
OR NON-INFRINGEMENT. NOR DOES ECONET PROVIDE ANY WARRANTY 
WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTIES WHICH 
MAY BE USED BY, INCORPORATED IN, OR SUPPLIED WITH THE ECONET SOFTWARE. 
RECEIVER AGREES TO LOOK ONLY TO SUCH THIRD PARTIES FOR ANY AND ALL 
WARRANTY CLAIMS RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES 
THAT IT IS RECEIVER’S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD 
PARTY ALL PROPER LICENSES CONTAINED IN ECONET SOFTWARE.

ECONET SHALL NOT BE RESPONSIBLE FOR ANY ECONET SOFTWARE RELEASES 
MADE TO RECEIVER’S SPECIFICATION OR CONFORMING TO A PARTICULAR 
STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND 
ECONET'S ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE ECONET 
SOFTWARE RELEASED HEREUNDER SHALL BE, AT ECONET'S SOLE OPTION, TO 
REVISE OR REPLACE THE ECONET SOFTWARE AT ISSUE OR REFUND ANY SOFTWARE 
LICENSE FEES OR SERVICE CHARGES PAID BY RECEIVER TO ECONET FOR SUCH 
ECONET SOFTWARE.
***************************************************************/
#ifndef _XPON_GLOBAL_PUBLIC_XMCS_IF_H_
#define _XPON_GLOBAL_PUBLIC_XMCS_IF_H_

#include "xmcs_const.h"

#define XPON_QUEUE_NUMBER			8

/**************************************************/
/* struct definition for EPON/GPON common command */
/**************************************************/
typedef struct XMCS_WanCntStats_S {
	__u32							mask;
	__u32							txFrameCnt;
	unsigned long long				txFrameLen;
	__u32							txDropCnt;
	__u32							txBroadcastCnt;
	__u32							txMulticastCnt;
	__u32							txLess64Cnt;
	__u32							txMore1518Cnt;
	__u32							tx64Cnt;
	__u32							tx65To127Cnt;
	__u32							tx128To255Cnt;
	__u32							tx256To511Cnt;
	__u32							tx512To1023Cnt;
	__u32							tx1024To1518Cnt;
	
	__u32							rxFrameCnt;
	unsigned long long				rxFrameLen;
	__u32							rxDropCnt;
	__u32							rxBroadcastCnt;
	__u32							rxMulticastCnt;
	__u32							rxCrcCnt;
	__u32							rxFragFameCnt;
	__u32							rxJabberFameCnt;
	__u32							rxLess64Cnt;
	__u32							rxMore1518Cnt;
	__u32							rx64Cnt;
	__u32							rx65To127Cnt;
	__u32							rx128To255Cnt;
	__u32							rx256To511Cnt;
	__u32							rx512To1023Cnt;
	__u32							rx1024To1518Cnt;

	__u32							rxHecErrorCnt;
	__u32							rxFecErrorCnt;
	__u32							rxFecCerrorCnt;
	__u32							FecSeconds;
	__u32							BipError;
}WAN_STATISTIC_t;

typedef enum {
    NO_ENCRYPTION = 0,
    GPON_UNICAST_ENCRYPTION,
    GPON_BROADCAST_ENCRYPTION,
	GPON_UNICAST_ENCRYPTION_ONLY_DOWN,	
} GPON_GemEncryption_t;

typedef enum {
	GPON_UNICAST_GEM = 0,
	GPON_MULTICAST_GEM,
} GPON_GemType_t ;

#ifdef TCSUPPORT_WAN_EPON
/* enum definition for EPON */
typedef enum {
	EPON_RX_FORWARDING = 0,
	EPON_RX_DISCARD,
	EPON_RX_LOOPBACK
} EPON_RxMode_t ;

typedef enum {
	EPON_TX_FORWARDING = 0,
	EPON_TX_DISCARD,
} EPON_TxMode_t ;

/* struct definition for EPON */
struct XMCS_EponLlidCreate_S {
	__u8 		idx ;
	__u16		llid ;
} ;

typedef struct XMCS_EponRxConfig_S {
	__u8 			idx ;
	EPON_RxMode_t	rxMode ;
}EponRxConfig_t ;

typedef struct XMCS_EponTxConfig_S {
	__u8			idx ;
	EPON_TxMode_t	txMode ;
}EponTxConfig_t;

struct XMCS_EponLlidInfo_S {
	struct {
		__u8 				idx ;
		__u16 				llid ;
		__u8				channel ;
		EPON_RxMode_t		rxMode ;
		EPON_TxMode_t		txMode ;
	} info[CONFIG_EPON_MAX_LLID] ;
	__u16 entryNum ; 
} ;
#endif /* TCSUPPORT_WAN_EPON */

typedef enum {
	XMCS_IF_WEIGHT_TYPE_PACKET = 0,
	XMCS_IF_WEIGHT_TYPE_BYTE
} XMCSIF_QoSWeightType_t ;

typedef enum {
	XMCS_IF_WEIGHT_SCALE_64B = 0,
	XMCS_IF_WEIGHT_SCALE_16B,
	XMCS_IF_WEIGHT_SCALE_1B
} XMCSIF_QoSWeightScale_t ;

typedef enum {
	XMCS_IF_QOS_TYPE_WRR = 0,
	XMCS_IF_QOS_TYPE_SP,
	XMCS_IF_QOS_TYPE_SPWRR7, 
	XMCS_IF_QOS_TYPE_SPWRR6, 
	XMCS_IF_QOS_TYPE_SPWRR5, 
	XMCS_IF_QOS_TYPE_SPWRR4, 
	XMCS_IF_QOS_TYPE_SPWRR3, 
	XMCS_IF_QOS_TYPE_SPWRR2, 
} XMCSIF_QosType_t ;

typedef enum {
	XMCS_IF_CONGESTIOM_SCALE_2 = 0,
	XMCS_IF_CONGESTIOM_SCALE_4,
	XMCS_IF_CONGESTIOM_SCALE_8,
	XMCS_IF_CONGESTIOM_SCALE_16,
} XMCSIF_CongestionScale_t ;

typedef enum {
	XMCS_IF_TRTCM_SCALE_1B = 0,
	XMCS_IF_TRTCM_SCALE_2B,
	XMCS_IF_TRTCM_SCALE_4B, 
	XMCS_IF_TRTCM_SCALE_8B,
	XMCS_IF_TRTCM_SCALE_16B,
	XMCS_IF_TRTCM_SCALE_32B,
	XMCS_IF_TRTCM_SCALE_64B,
	XMCS_IF_TRTCM_SCALE_128B,
	XMCS_IF_TRTCM_SCALE_256B,
	XMCS_IF_TRTCM_SCALE_512B,
	XMCS_IF_TRTCM_SCALE_1K,
	XMCS_IF_TRTCM_SCALE_2K,
	XMCS_IF_TRTCM_SCALE_4K,
	XMCS_IF_TRTCM_SCALE_8K,
	XMCS_IF_TRTCM_SCALE_16K,
	XMCS_IF_TRTCM_SCALE_32K,
	XMCS_IF_TRTCM_SCALE_ITEMS
} XMCSIF_TrtcmScale_t ;


struct XMCS_QoSWeightConfig_S {
	XMCSIF_QoSWeightType_t		weightType ;
	XMCSIF_QoSWeightScale_t		weightScale ;
};

struct XMCS_ChannelQoS_S {
	__u8						channel ;
	XMCSIF_QosType_t			qosType ;
	struct {
		__u8					weight ;
	} queue[XPON_QUEUE_NUMBER];
};

struct XMCS_TxQueueCongestion_S {
	struct {
		XPON_Mode_t				trtcm ;
		XPON_Mode_t				dei ;
		XPON_Mode_t				threshold ;
	} congestMode ;
	struct {
		XMCSIF_CongestionScale_t	max ;
		XMCSIF_CongestionScale_t	min ;
	} scale ;
	struct {
		__u8					green ;
		__u8					yellow ;
	} dropProbability ;
	struct {
		__u8					queueIdx ;
		__u8					greenMax ;
		__u8					greenMin ;
		__u8					yellowMax ;
		__u8					yellowMin ;
	} queueThreshold[XPON_QUEUE_NUMBER] ;
};

struct XMCS_TxTrtcmScale_S {
	XMCSIF_TrtcmScale_t			trtcmScale ;
};

struct XMCS_TxQueueTrtcm_S {
	__u8						tsIdx ;
	__u16						cirValue ;
	__u16						cbsUnit ;
	__u16						pirValue ;
	__u16						pbsUnit ;
};

typedef enum {
	XMCS_IF_ONU_TYPE_UNKNOWN = 0,
	XMCS_IF_ONU_TYPE_SFU,
	XMCS_IF_ONU_TYPE_HGU
} XMCSIF_OnuType_t;

typedef struct {
	unsigned char mac[6];
} XMCSIF_OnuMac_t;

typedef enum {
	XMCS_IF_WAN_DETECT_MODE_AUTO = 0,
	XMCS_IF_WAN_DETECT_MODE_GPON,
	XMCS_IF_WAN_DETECT_MODE_EPON,
	XMCS_IF_WAN_DETECT_MODE_10G_1G_EPON,
	XMCS_IF_WAN_DETECT_MODE_10G_10G_EPON,
	XMCS_IF_WAN_DETECT_MODE_1G_1G_EPON,
	XMCS_IF_WAN_DETECT_MODE_XGPON,
    XMCS_IF_WAN_DETECT_MODE_XGSPON,
    XMCS_IF_WAN_DETECT_MODE_NGPON2_10G_10G,
    XMCS_IF_WAN_DETECT_MODE_NGPON2_10G_2G,
    XMCS_IF_WAN_DETECT_MODE_NGPON2_2G_2G,
	/*add new mode above this line!*/
	XMCS_IF_WAN_DETECT_MODE_MAX,
} XMCSIF_WanDetectionMode_t ;
typedef enum {
	XMCS_IF_WAN_LINK_OFF = 0,
	XMCS_IF_WAN_LINK_GPON,
	XMCS_IF_WAN_LINK_EPON
} XMCSIF_WanLinkStatus_t ;

typedef struct XMCS_WanLinkConfig_S {
	XPON_Mode_t					linkStart ;
	XMCSIF_WanDetectionMode_t	detectMode ;
	XMCSIF_WanLinkStatus_t		linkStatus ;
}WAN_LINKCFG_t;

#ifdef TCSUPPORT_WAN_GPON
struct XMCS_GemPortInfo_S {
	struct {
		GPON_GemType_t		gemType ;
		__u16 				gemPortId ;	//gem id
		__u16 				allocId ;	//alloc id
		__u16 				aniIdx ;	//interface index
		XPON_Mode_t 		lbMode ;	//downstream loopback mode
		XPON_Mode_t			enMode ;	//downstream encryption mode
		XPON_Mode_t         txEncrypt; /*10G gemport tx encryption*/
	} info[CONFIG_GPON_MAX_GEMPORT] ;
	__u16 entryNum ; 
} ;
#endif

#endif /* _XPON_GLOBAL_PUBLIC_XMCS_IF_H_ */

