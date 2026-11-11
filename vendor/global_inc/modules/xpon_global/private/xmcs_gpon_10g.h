/***************************************************************
Copyright Statement:

This software/firmware and related documentation (¡°EcoNet Software¡±) 
are protected under relevant copyright laws. The information contained herein 
is confidential and proprietary to EcoNet (HK) Limited (¡°EcoNet¡±) and/or 
its licensors. Without the prior written permission of EcoNet and/or its licensors, 
any reproduction, modification, use or disclosure of EcoNet Software, and 
information contained herein, in whole or in part, shall be strictly prohibited.

EcoNet (HK) Limited  EcoNet. ALL RIGHTS RESERVED.

BY OPENING OR USING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY 
ACKNOWLEDGES AND AGREES THAT THE SOFTWARE/FIRMWARE AND ITS 
DOCUMENTATIONS (¡°ECONET SOFTWARE¡±) RECEIVED FROM ECONET 
AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON AN ¡°AS IS¡± 
BASIS ONLY. ECONET EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, 
WHETHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, 
OR NON-INFRINGEMENT. NOR DOES ECONET PROVIDE ANY WARRANTY 
WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTIES WHICH 
MAY BE USED BY, INCORPORATED IN, OR SUPPLIED WITH THE ECONET SOFTWARE. 
RECEIVER AGREES TO LOOK ONLY TO SUCH THIRD PARTIES FOR ANY AND ALL 
WARRANTY CLAIMS RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES 
THAT IT IS RECEIVER¡¯S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD 
PARTY ALL PROPER LICENSES CONTAINED IN ECONET SOFTWARE.

ECONET SHALL NOT BE RESPONSIBLE FOR ANY ECONET SOFTWARE RELEASES 
MADE TO RECEIVER¡¯S SPECIFICATION OR CONFORMING TO A PARTICULAR 
STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND 
ECONET'S ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE ECONET 
SOFTWARE RELEASED HEREUNDER SHALL BE, AT ECONET'S SOLE OPTION, TO 
REVISE OR REPLACE THE ECONET SOFTWARE AT ISSUE OR REFUND ANY SOFTWARE 
LICENSE FEES OR SERVICE CHARGES PAID BY RECEIVER TO ECONET FOR SUCH 
ECONET SOFTWARE.
***************************************************************/
#ifndef _XPON_GLOBAL_PRIVATE_XMCS_GPON_10G_H_
#define _XPON_GLOBAL_PRIVATE_XMCS_GPON_10G_H_

/************************************************************************
*               I N C L U D E S
*************************************************************************
*/
#include "../public/xmcs_gpon_10g.h"
#include "xmcs_const.h"

/************************************************************************
*               D E F I N E S   &   C O N S T A N T S
*************************************************************************
*/

/* struct definition for XGPON common command */
struct XMCS_XgponSn_S {
    __u8  sn[GPON_SN_LENS] ;
    __u8  EmergencyState  ;
} ;

struct XMCS_XgponActTimer_S {
    __u32    to1Timer ;
    __u32    to2Timer ;
} ;

struct XGMCS_XgponMsk_S {
    __u8  msk[GPON_MSK_LENS];
} ;

struct XGMCS_XgponBroadcast_Key_S {
	__u8  keyIndex;
	__u8  keyFragmentNum;
	__u8  keyFragmentIndex;
    __u8  key[16];
} ;


typedef enum {
	XGPON_EQD_OFFSET_FLAG_ADD = 0,
	XGPON_EQD_OFFSET_FLAG_SUBTRACT,
} XGPON_EQD_OFFSET_FLAG_t ;

typedef enum {
    WAN_MODE_XGPON = 0,
    WAN_MODE_XGSPON,
    WAN_MODE_NGPON2,
} GPON_10G_DEV_WAN_MODE_T ;

/**********************************************************************************
***********************************************************************************/
#define GPON_10G_MAGIC                       (0xDC)

/* XGPON IO Command */
#define GPON_10G_IOS_SN                        _IOW(GPON_10G_MAGIC, 0x01, struct XMCS_XgponSn_S *)
#define GPON_10G_IOS_ACT_TIMER                 _IOW(GPON_10G_MAGIC, 0x02, struct XMCS_XgponActTimer_S *)
#define GPON_10G_IOS_MSK         		       _IOW(GPON_10G_MAGIC, 0x03, struct XGMCS_XgponMsk_S *)
#define GPON_10G_IOS_BROADCAST_KEY             _IOW(GPON_10G_MAGIC, 0x04, struct XGMCS_XgponBroadcast_Key_S *)
#define GPON_10G_IOS_O23_O4_PLOAM_CTRL         _IOW(GPON_10G_MAGIC, 0x05, XGPON_SW_HW_SELECT_T )
#define GPON_10G_IOG_O23_O4_PLOAM_CTRL         _IOR(GPON_10G_MAGIC, 0x05, XGPON_SW_HW_SELECT_T *)
#define GPON_10G_IOG_EQD_OFFSET                _IOR(GPON_10G_MAGIC, 0x06, struct XGMCS_EqdOffset_S *)
#define GPON_10G_IOS_EQD_OFFSET_FLAG           _IOW(GPON_10G_MAGIC, 0x07, char)
#define GPON_10G_IOS_EQD_OFFSET_O4             _IOW(GPON_10G_MAGIC, 0x08, __u8)
#define GPON_10G_IOS_EQD_OFFSET_O5             _IOW(GPON_10G_MAGIC, 0x09, __u8)
#define GPON_10G_IOG_ONU_INFO                  _IOR(GPON_10G_MAGIC, 0x10, struct XGMCS_XgponOnuInfo_S *)
#define GPON_10G_IOS_SNIFFER_GTC               _IOW(GPON_10G_MAGIC, 0x11, GPON_10G_DEV_SNIFFER_MODE_T *)
#define GPON_10G_IOG_SNIFFER_GTC               _IOR(GPON_10G_MAGIC, 0x12, GPON_10G_DEV_SNIFFER_MODE_T *)
#define GPON_10G_IOS_PLOAM_FILTER              _IOW(GPON_10G_MAGIC, 0x13, GPON_10G_DEV_PLOAMD_FILTER_MODE_T *)
#define GPON_10G_IOG_PLOAM_FILTER              _IOR(GPON_10G_MAGIC, 0x14, GPON_10G_DEV_PLOAMD_FILTER_MODE_T *)
#define GPON_10G_IOS_WAN_MODE              	   _IOW(GPON_10G_MAGIC, 0x15, GPON_10G_DEV_WAN_MODE_T )
#define GPON_10G_IOG_WAN_MODE             	   _IOR(GPON_10G_MAGIC, 0x16, __u32 *)
#define GPON_10G_IOS_ERR_PLOAM_DROP            _IOW(GPON_10G_MAGIC, 0x17, XPON_Mode_t )
#define GPON_10G_IOG_ERR_PLOAM_DROP            _IOR(GPON_10G_MAGIC, 0x18, XPON_Mode_t )
#define GPON_10G_IOS_SW_DYING_GASP             _IOW(GPON_10G_MAGIC, 0x19, XPON_Mode_t )
#define GPON_10G_IOG_SW_DYING_GASP             _IOR(GPON_10G_MAGIC, 0x20, XPON_Mode_t *)
#define GPON_10G_IOS_PHY_MODE 			       _IOW(GPON_10G_MAGIC, 0x21, struct XGMCSIF_PhyMode_t *)
#define GPON_10G_IOS_ACK_SEND 			       _IOW(GPON_10G_MAGIC, 0x22, __u8)
#define GPON_10G_IOS_DBA_BACKDOOR              _IOW(GPON_10G_MAGIC, 0x23, GPON_10G_DEV_DBA_BACKDOOR_T *)
#define GPON_10G_IOG_DBA_BACKDOOR              _IOR(GPON_10G_MAGIC, 0x24, GPON_10G_DEV_DBA_BACKDOOR_T *)
#define GPON_10G_IOS_OMCI_MIC_CTRL             _IOW(GPON_10G_MAGIC, 0x25, GPON_10G_DEV_OMCI_MIC_CTRL_T *)
#define GPON_10G_IOG_OMCI_MIC_CTRL             _IOR(GPON_10G_MAGIC, 0x26, GPON_10G_DEV_OMCI_MIC_CTRL_T *)
#define GPON_10G_IOS_OMCI_BROADCAST_KEY        _IOW(GPON_10G_MAGIC, 0x27, __u8 *)
#define GPON_10G_IOC_OMCI_BROADCAST_KEY        _IOW(GPON_10G_MAGIC, 0x28, __u8 *)
#define GPON_10G_IOS_CLEAR_GEM_COUNTER         _IOW(GPON_10G_MAGIC, 0x29, __u16)
#define GPON_10G_IOG_GEM_COUNTER               _IOR(GPON_10G_MAGIC, 0x30, struct XMCS_CounterCfg_S *)
#define GPON_10G_IOS_COUNTER_TYPE              _IOW(GPON_10G_MAGIC, 0x31, GPON_10G_COUNTER_TYPE_t)
#define GPON_10G_IOG_COUNTER_TYPE              _IOR(GPON_10G_MAGIC, 0x32, GPON_10G_COUNTER_TYPE_t *)
#define GPON_10G_IOS_SW_RESET                  _IOW(GPON_10G_MAGIC, 0x33, ulong)
#define GPON_10G_IOS_CLEAR_All_COUNTER         _IOW(GPON_10G_MAGIC, 0x34, __u32)
#define GPON_10G_IOS_TC_COUNTER                _IOR(GPON_10G_MAGIC, 0x35, GPON_10G_TC_COUNTER_T *)


/************************************************************************
*               M A C R O S
*************************************************************************
*/

/************************************************************************
*               D A T A   T Y P E S
*************************************************************************
*/

/************************************************************************
*               D A T A   D E C L A R A T I O N S
*************************************************************************
*/

/************************************************************************
*               F U N C T I O N   D E C L A R A T I O N S
                I N L I N E  F U N C T I O N  D E F I N I T I O N S
*************************************************************************
*/




#endif /* _XPON_GLOBAL_PRIVATE_XMCS_GPON_10G_H_ */
