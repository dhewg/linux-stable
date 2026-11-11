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
#ifndef _XPON_GLOBAL_PRIVATE_XMCS_PHY_H_
#define _XPON_GLOBAL_PRIVATE_XMCS_PHY_H_

#include "../public/xmcs_phy.h"
#include "xmcs_const.h"

/* 
    enum definition for PHY command 
*/
typedef enum {
	XMCS_PHY_BURST_MODE = 0,
	XMCS_PHY_CONTINUOUS_MODE
} XMCSPHY_TxBurstMode_t ;


/* 
    struct definition for PHY command 
*/
struct XMCS_PhyFrameCount_S {
	XPON_Mode_t		frameCntReset ;
	struct {
		__u32		low ;
		__u32		high ;
		__u32		lof ;
	} frameCounter ;
} ;

struct XMCS_PhyTransSetting_S {
	XPON_Mode_t		txSdInverse ;
	XPON_Mode_t		txFaultInverse ;
	XPON_Mode_t		txBurstEnInverse ;
	XPON_Mode_t		rxSdInverse ;
} ;

struct XMCS_PhyTxBurstCfg_S {
	XMCSPHY_TxBurstMode_t	burstMode ;
} ;
		
struct XMCS_PHY_I2cCtrl_S
{
	__u8  u1CHannelID;
	__u16 u2ClkDiv;
	__u8  u1DevAddr;
	__u8  u1WordAddrNum;
	__u32 u4WordAddr;
	__u8  * pu1Buf;
	__u16 u2ByteCnt;
};


/* 
    PHY IOCTL commands  
*/

#define PHY_MAGIC						0xD7

/* PHY IO Command */
#define PHY_IOS_FEC_MODE				_IOW(PHY_MAGIC, 0x01, struct XMCS_PhyRxFecConfig_S *)
#define PHY_IOG_FEC_STATUS				_IOR(PHY_MAGIC, 0x01, struct XMCS_PhyRxFecConfig_S *)
#define PHY_IOS_FEC_CLEAR				_IOW(PHY_MAGIC, 0x02, struct XMCS_PhyRxFecConfig_S *)
#define PHY_IOG_FEC_COUNTER				_IOR(PHY_MAGIC, 0x02, struct XMCS_PhyRxFecConfig_S *)
#define PHY_IOS_FRAME_CLEAR				_IOW(PHY_MAGIC, 0x03, struct XMCS_PhyFrameCount_S *)
#define PHY_IOG_FRAME_COUNTER			_IOR(PHY_MAGIC, 0x03, struct XMCS_PhyFrameCount_S *)
#define PHY_IOS_TRANSCEIVER_CONFIG		_IOW(PHY_MAGIC, 0x04, struct XMCS_PhyTransSetting_S *)
#define PHY_IOG_TRANSCEIVER_CONFIG		_IOR(PHY_MAGIC, 0x04, struct XMCS_PhyTransSetting_S *)
#define PHY_IOG_TRANSCEIVER_PARAMS		_IOR(PHY_MAGIC, 0x05, struct XMCS_PhyTransParams_S *)
#define PHY_IOS_TX_BURST_CONFIG			_IOW(PHY_MAGIC, 0x06, struct XMCS_PhyTxBurstCfg_S *)
#define PHY_IOG_TX_BURST_CONFIG			_IOR(PHY_MAGIC, 0x06, struct XMCS_PhyTxBurstCfg_S *)
#define PHY_IOG_TX_RX_FEC_STATUS		_IOR(PHY_MAGIC, 0x07, struct XMCS_PhyTxRxFecStatus_S *)
#define PHY_IOS_ROUGE_MODE				_IOW(PHY_MAGIC, 0x08, __u8)
#define PHY_IOS_I2C_CTRL_WRITE			_IOW(PHY_MAGIC, 0x09, struct XMCS_PHY_I2cCtrl_S *)
#define PHY_IOG_I2C_CTRL_READ			_IOR(PHY_MAGIC, 0x09, struct XMCS_PHY_I2cCtrl_S *)


#endif /* _XPON_GLOBAL_PRIVATE_XMCS_PHY_H_  */

