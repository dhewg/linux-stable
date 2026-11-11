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
#ifndef _XPON_GLOBAL_PRIVATE_XMCS_IF_H_
#define _XPON_GLOBAL_PRIVATE_XMCS_IF_H_


#include "../public/xmcs_if.h"
#include "xmcs_const.h"

/* enum definition for EPON/GPON common command */

typedef enum {
	XMCS_IF_PCP_TYPE_CDM_TX = 0,
	XMCS_IF_PCP_TYPE_CDM_RX, 
	XMCS_IF_PCP_TYPE_GDM_RX
} XMCSIF_PcpType_t ;

typedef enum {
	XMCS_IF_PCP_MODE_DISABLE = 0,
	XMCS_IF_PCP_MODE_8B0D,
	XMCS_IF_PCP_MODE_7B1D, 
	XMCS_IF_PCP_MODE_6B2D,
	XMCS_IF_PCP_MODE_5B3D
} XMCSIF_PcpMode_t ;

typedef enum {
	SYS_GPON_MODE = 0,
	SYS_EPON_MODE,
	SYS_PTM_MODE,
	SYS_ATM_MODE,
	SYS_reserved_MODE,
	SYS_GPON_P2P_MODE,
	SYS_10G_1G_EPON_MODE ,
	SYS_10G_10G_EPON_MODE,
	SYS_1G_1G_EPON_MODE,
	SYS_XGPON_MODE,
	SYS_XGSPON_MODE,
    SYS_NGPON2_10G_10G_MODE,
    SYS_NGPON2_10G_2G_MODE,
    SYS_NGPON2_2G_2G_MODE,
	/*add new mode above this line!*/
	SYS_WAN_MODE_MAX,
} SCU_WanMode_t ;


typedef enum {
	XMCS_IF_CLEAR_TYPE_XPON = 0,
} XMCSIF_ClearType_t;

/**************************************************/
/* struct definition for EPON/GPON common command */
/**************************************************/
struct XMCS_DebugLevel_S {
	xPON_DebugMsg_t mask;
	XPON_Mode_t enable;
};

struct XMCS_TxPCPConfig_S {
	XMCSIF_PcpType_t			pcpType ;
	XMCSIF_PcpMode_t			pcpMode ;
};

struct XMCS_ClearConfig_S  {
	XMCSIF_ClearType_t			clearType ;
};


struct XMCS_StormCtrlConfig_S {
	__u32				mask;
	__u32 				threld ;
	__u32 				timer ;
};

#if defined(TCSUPPORT_XPON_HAL_API_QOS) || defined(TCSUPPORT_XPON_HAL_API_EXT)
struct XMCS_QosPolicerCreat_S {
	__u32                policer_id;
	__u32                cir;
};

struct XMCS_QosPolicerDelete_S {
    __u32                policer_id;
};

struct XMCS_OverallRatelimitConfig_S {
    __u32                bandwidth;
};
#endif

#ifdef TCSUPPORT_WAN_GPON

/* struct definition for GPON */
struct XMCS_GemPortAssign_S {
	struct {
		__u16 id ;
		__u16 ani ;
	} gemPort[CONFIG_GPON_MAX_GEMPORT] ;
	__u16 entryNum ;
};

struct XMCS_GemPortCreate_S {
	GPON_GemType_t		gemType ;
	__u16 				gemPortId ;
	__u16 				allocId ;
    GPON_GemEncryption_t gemEncrypt;
};

struct XMCS_GemPortLoopback_S {
	__u16 		gemPortId ;
	XPON_Mode_t	loopback ;
};

struct XMCS_TcontInfo_S {
	struct {
		__u16 			allocId ;
		__u8 			channel ;
	} info[CONFIG_GPON_MAX_TCONT] ;
	__u16 entryNum ; 
} ;

struct XMCS_TcontCfg_S {
	__u16 			allocId ;	
	__u8 			tcontId ;
	__u8 			tcontPolicy ; 
} ;

struct XMCS_OMCC_Info_S {
    __u16  allocId;
    __u32    gemportid;
} ;

struct XMCS_TcontTrtcmScale {
	XMCSIF_TrtcmScale_t			trtcmScale ;
} ;

struct XMCS_TcontTrtcm_S {
	struct {
		__u8					channel ;
		__u32					cirValue ;
		__u32					cbsUnit ;
		__u32					pirValue ;
		__u32					pbsUnit ;
	} trtcmParam[CONFIG_GPON_MAX_TCONT] ;
	__u8 entryNum ;
} ;
#endif /* TCSUPPORT_WAN_GPON */

/**********************************************************************************
***********************************************************************************/

#define INTERFACE_MAGIC						(0xDA)

/* Interface IO Command */
#define IF_IOS_QOS_WEIGHT_CONFIG			_IOW(INTERFACE_MAGIC, 0x01, struct XMCS_QoSWeightConfig_S *)
#define IF_IOG_QOS_WEIGHT_CONFIG			_IOR(INTERFACE_MAGIC, 0x01, struct XMCS_QoSWeightConfig_S *)
#define IF_IOS_QOS_SCHEDULER				_IOW(INTERFACE_MAGIC, 0x02, struct XMCS_ChannelQoS_S *)
#define IF_IOG_QOS_SCHEDULER				_IOR(INTERFACE_MAGIC, 0x02, struct XMCS_ChannelQoS_S *)
#define IF_IOS_TRTCM_CONGEST_MODE			_IOW(INTERFACE_MAGIC, 0x03, struct XMCS_TxQueueCongestion_S *)
#define IF_IOS_DEI_CONGEST_MODE				_IOW(INTERFACE_MAGIC, 0x04, struct XMCS_TxQueueCongestion_S *)
#define IF_IOS_THRESHOLD_CONGEST_MODE		_IOW(INTERFACE_MAGIC, 0x05, struct XMCS_TxQueueCongestion_S *)
#define IF_IOS_CONGEST_SCALE				_IOW(INTERFACE_MAGIC, 0x06, struct XMCS_TxQueueCongestion_S *)
#define IF_IOS_CONGEST_DROP_PROBABILITY		_IOW(INTERFACE_MAGIC, 0x07, struct XMCS_TxQueueCongestion_S *)
#define IF_IOS_CONGEST_THRESHOLD			_IOW(INTERFACE_MAGIC, 0x08, struct XMCS_TxQueueCongestion_S *)
#define IO_IOG_CONGEST_INFO					_IOR(INTERFACE_MAGIC, 0x09, struct XMCS_TxQueueCongestion_S *)
#define IO_IOS_TX_TRTCM_SCALE				_IOW(INTERFACE_MAGIC, 0x0A, struct XMCS_TxTrtcmScale_S *)
#define IO_IOG_TX_TRTCM_SCALE				_IOR(INTERFACE_MAGIC, 0x0A, struct XMCS_TxTrtcmScale_S *)
#define IO_IOS_TX_TRTCM_PARAMS				_IOW(INTERFACE_MAGIC, 0x0B, struct XMCS_TxQueueTrtcm_S *)
#define IO_IOG_TX_TRTCM_PARAMS				_IOR(INTERFACE_MAGIC, 0x0B, struct XMCS_TxQueueTrtcm_S *)
#define IO_IOS_PCP_CONFIG					_IOW(INTERFACE_MAGIC, 0x0C, struct XMCS_TxPCPConfig_S *)
#define IO_IOG_PCP_CONFIG					_IOR(INTERFACE_MAGIC, 0x0C, struct XMCS_TxPCPConfig_S *)
#define IO_IOS_WAN_LINK_START				_IOW(INTERFACE_MAGIC, 0x20, XPON_Mode_t)
#define IO_IOS_WAN_DETECTION_MODE			_IOW(INTERFACE_MAGIC, 0x21, XMCSIF_WanDetectionMode_t)
#define IO_IOG_WAN_LINK_CONFIG				_IOR(INTERFACE_MAGIC, 0x22, struct XMCS_WanLinkConfig_S *)
#define IO_IOG_ONU_TYPE						_IOR(INTERFACE_MAGIC, 0x23, XMCSIF_OnuType_t *)
#define IO_IOS_WAN_CNT_STATS				_IOW(INTERFACE_MAGIC, 0x24, struct XMCS_WanCntStats_S *)
#define IO_IOG_WAN_CNT_STATS				_IOR(INTERFACE_MAGIC, 0x24, struct XMCS_WanCntStats_S *)
#define IO_IOS_STORM_CTL_CONFIG				_IOW(INTERFACE_MAGIC, 0x25, struct XMCS_StormCtrlConfig_S *)
#define IO_IOG_STORM_CTL_CONFIG				_IOR(INTERFACE_MAGIC, 0x25, struct XMCS_StormCtrlConfig_S *)

#if defined(TCSUPPORT_XPON_HAL_API_QOS) || defined(TCSUPPORT_XPON_HAL_API_EXT)
    #define IO_IOS_QOS_CREAT_POLICER			_IOW(INTERFACE_MAGIC, 0x26, struct XMCS_QosPolicerCreat_S *)
    #define IO_IOS_QOS_DELETE_POLICER			_IOW(INTERFACE_MAGIC, 0x27, struct XMCS_QosPolicerDelete_S *)
    #define IO_IOS_QOS_OVERALL_RATELIMIT_CONFIG	_IOW(INTERFACE_MAGIC, 0x28, struct XMCS_OverallRatelimitConfig_S *)
#endif

#define IO_IOS_DBG_LEVEL					_IOW(INTERFACE_MAGIC, 0x29, struct XMCS_DebugLevel_S *)
#define IO_IOG_DBG_LEVEL                    _IOR(INTERFACE_MAGIC, 0x29, __u16 *)
#define IO_IOG_PLOAM_GTC_INFO               _IOR(INTERFACE_MAGIC, 0x2A, PLOAM_GTC_INFO_T *)
#define IF_IOS_ROGUE_MODE                   _IOW(INTERFACE_MAGIC, 0x2B, __u8)
#define IO_IOG_DRV_POWER_LEVEL              _IOR(INTERFACE_MAGIC, 0x2C, PLOAM_POWER_LEVEL_T *)
#ifdef TCSUPPORT_CPU_EN7521
#define IO_IOG_ALL_TCONT_PACKET_INFO        _IOR(INTERFACE_MAGIC, 0x2D, ALL_TCONT_COUNTERS_T *)
#define IO_IOG_TCONT_PACKET_INFO            _IOR(INTERFACE_MAGIC, 0x2E, TCONT_COUNTERS_T *)
#endif
#define IO_IOG_GET_ONLINE_DURATION          _IOR(INTERFACE_MAGIC, 0x2F, __u32)
#define IO_IOG_ONU_MODE						_IOR(INTERFACE_MAGIC, 0x30, XMCSIF_WanDetectionMode_t *)
#define IO_IOG_ONU_MAC						_IOR(INTERFACE_MAGIC, 0x31, XMCSIF_OnuMac_t*)
#define IO_IOG_ONU_MODE_FROM_FLASH			_IOR(INTERFACE_MAGIC, 0x32, __u8 *)

#ifdef TCSUPPORT_WAN_GPON
	#define IF_IOS_INTERFACE_CREATE			_IOW(INTERFACE_MAGIC, 0x40, __u32)
	#define IF_IOS_INTERFACE_DELETE			_IOW(INTERFACE_MAGIC, 0x41, __u32)
	#define IF_IOS_GEMPORT_ASSIGN			_IOW(INTERFACE_MAGIC, 0x42, struct XMCS_GemPortAssign_S *)
	#define IF_IOS_GEMPORT_UNASSIGN			_IOW(INTERFACE_MAGIC, 0x43, struct XMCS_GemPortAssign_S *)
	#define IF_IOS_GEMPORT_CREATE			_IOW(INTERFACE_MAGIC, 0x44, struct XMCS_GemPortCreate_S *)
	#define IF_IOS_GEMPORT_REMOVE			_IOW(INTERFACE_MAGIC, 0x45, __u32)
	#define IF_IOS_GEMPORT_REMOVE_ALL		_IOW(INTERFACE_MAGIC, 0x46, __u32)
	#define IF_IOS_GEMPORT_LOOPBACK			_IOW(INTERFACE_MAGIC, 0x47, struct XMCS_GemPortLoopback_S *)
	#define IF_IOG_GEMPORT_INFO				_IOR(INTERFACE_MAGIC, 0x48, struct XMCS_GemPortInfo_S *)
	#define IF_IOG_TCONT_INFO				_IOR(INTERFACE_MAGIC, 0x49, struct XMCS_TcontInfo_S *)
	#define IF_IOS_TCONT_INFO_CREATE		_IOW(INTERFACE_MAGIC, 0x4A, struct XMCS_TcontCfg_S *)
	#define IF_IOS_TCONT_INFO_REMOVE		_IOW(INTERFACE_MAGIC, 0x4B, struct XMCS_TcontCfg_S *)
	#define IF_IOG_OMCC_INFO				_IOR(INTERFACE_MAGIC, 0x4C, __u16 *)
	#define IF_IOS_GPON_SILENCE				_IOW(INTERFACE_MAGIC, 0x4F, __u32)
	#define IF_IOG_ALLOCID_INFO             _IOW(INTERFACE_MAGIC, 0x50, __u16)
#endif /* TCSUPPORT_WAN_GPON */

#ifdef TCSUPPORT_WAN_EPON
	#define IF_IOS_LLID_CREATE				_IOW(INTERFACE_MAGIC, 0x81, struct XMCS_EponLlidCreate_S *)
	#define IF_IOS_LLID_REMOVE				_IOW(INTERFACE_MAGIC, 0x82, __u32)
	#define IF_IOS_LLID_RX_CFG				_IOW(INTERFACE_MAGIC, 0x83, struct XMCS_EponRxConfig_S *)
	#define IF_IOS_LLID_TX_CFG				_IOW(INTERFACE_MAGIC, 0x84, struct XMCS_EponTxConfig_S *)
	#define IF_IOG_LLID_INFO				_IOR(INTERFACE_MAGIC, 0x85, struct XMCS_EponLlidInfo_S *)
#endif /* TCSUPPORT_WAN_EPON */



#endif /* _XPON_GLOBAL_PRIVATE_XMCS_IF_H_ */

