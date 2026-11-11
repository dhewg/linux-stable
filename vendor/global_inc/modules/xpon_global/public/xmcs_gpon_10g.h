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
#ifndef _XPON_GLOBAL_PUBLIC_XMCS_GPON_10G_H_
#define _XPON_GLOBAL_PUBLIC_XMCS_GPON_10G_H_

/************************************************************************
*               I N C L U D E S
*************************************************************************
*/
#include "xmcs_const.h"

/************************************************************************
*               D E F I N E S   &   C O N S T A N T S
*************************************************************************
*/

typedef enum {
	XGPON_SW = 0,
	XGPON_HW,
} XGPON_SW_HW_SELECT_T ;

typedef enum {
    GPON_DBA_BACKDOOR_NOT_MODIFY = 0,
    GPON_DBA_BACKDOOR_FIX_MODE ,
    GPON_DBA_BACKDOOR_ADD_MODE ,
    GPON_DBA_BACKDOOR_SHIFT_MODE ,
} GPON_10G_DEV_DBA_MODIFY_MODE_T ;

typedef enum {
    GPON_DBA_BACKDOOR_ADD = 0,
    GPON_DBA_BACKDOOR_MINUS ,
} GPON_10G_DEV_DBA_ADD_MODE_T ;

typedef enum {
    GPON_DBA_BACKDOOR_LEFT_SHIFT = 0,
    GPON_DBA_BACKDOOR_RIGHT_SHIFT ,
} GPON_10G_DEV_DBA_SHIFT_MODE_T ;

typedef struct {
   	GPON_10G_DEV_DBA_MODIFY_MODE_T mode;
    GPON_10G_DEV_DBA_ADD_MODE_T    addMode;
    GPON_10G_DEV_DBA_SHIFT_MODE_T  shiftMode;
    unsigned int                   value;
} GPON_10G_DEV_DBA_BACKDOOR_T;

typedef struct {
   	XGPON_SW_HW_SELECT_T     usOmciMicMode;
    XGPON_SW_HW_SELECT_T     dsOmciMicMode;
} GPON_10G_DEV_OMCI_MIC_CTRL_T;

typedef enum {
    GPON_10G_COUNTER_TYPE_GEM = 0,
    GPON_10G_COUNTER_TYPE_ETHERNET,
} GPON_10G_COUNTER_TYPE_t ;

typedef enum {
    GPON_10G_COUNTER_TYPE_ALL = 0,
    GPON_10G_COUNTER_TYPE_SPECIFIC,
} GPON_10G_CLEAR_COUNTER_TYPE_t ;

typedef struct {
   	GPON_10G_CLEAR_COUNTER_TYPE_t  clearType;
    unsigned int                   gemportId;
} GPON_10G_DEV_COUNTER_CLEAR_T;


struct XGMCS_EqdOffset_S {
    unsigned char O4 ;
    unsigned char O5 ;
    unsigned char eqdOffsetFlag;
} ;

typedef enum {
    GPON_10G_SNIFFER_MODE_LAN0 = 0x0001,
    GPON_10G_SNIFFER_MODE_LAN1 = 0x0002,
    GPON_10G_SNIFFER_MODE_LAN2 = 0x0004,
    GPON_10G_SNIFFER_MODE_LAN3 = 0x0008,
} GPON_10G_DEV_SNIFFER_MODE_LAN_PORT_T ;

typedef struct {
    GPON_10G_DEV_SNIFFER_MODE_LAN_PORT_T lan_port;
    __u16          tx_da;
    __u16          tx_sa;
    __u16          rx_da;
    __u16          rx_sa;
    __u16          ethertype;
    __u16          tpid;
    __u16          gemPortId;
	XPON_Mode_t     ds_enable;
    XPON_Mode_t     us_enable;
} GPON_10G_DEV_SNIFFER_MODE_T;

typedef struct {
    XGPON_SW_HW_SELECT_T dyingGaspCtrl;
	unsigned char        dyingGaspNum;
    unsigned char        hwDGStatus;
} GPON_10G_DYING_GASP_MODE_T;


typedef struct {
   	XPON_Mode_t     ploamd_filter; /*exclude profile ploam*/
    XPON_Mode_t     profile_filter;
} GPON_10G_DEV_PLOAMD_FILTER_MODE_T;

typedef enum {
	XGMCS_IF_PHY_LOSS = 0,
	XGMCS_IF_PHY_READY, 
} XGMCSIF_PhyMode_t;

typedef struct XGMCS_XgponOnuInfo_S {
    __u8  onuId ;
    __u8  state ;
    __u8  sn[GPON_SN_LENS] ;
    __u32    actTo1Timer ;
    __u32    actTo2Timer ;
    __u16  omcc ;
    __u8  EmergencyState ;
} XGPON_ONU_INFO_t;

typedef struct {
   	__u32 PSBdHECErrCount ;
    __u32 XGTCHECErrCount ;
    __u32 UnknownProfCount ;
    __u32 TransmitXGEMFrames ;
    __u32 FragmentXGEMFrames ;
    __u32 XGEMHECLostWordCount ;
    __u32 XGEMKeyErrors ;  
    __u32 XGEMHECErrCount ;    
    __u32 TransmitByteNoidleXGEMFrames ;
	__u32 ReceiveByteNoidleXGEMFrames ;  
    __u32 LODSEventCount ;    
    __u32 LODSEventRestoreCount ;
	__u32 ONUReactivLODSEvents ;
} GPON_10G_TC_COUNTER_T;

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



#endif /* _XPON_GLOBAL_PUBLIC_XMCS_GPON_10G_H_ */

