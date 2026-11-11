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
#ifndef _XPON_GLOBAL_PUBLIC_XMCS_GPON_H_
#define _XPON_GLOBAL_PUBLIC_XMCS_GPON_H_

#include "xmcs_const.h"
#define SC_PLOAM_NUM_DELIMITER_BYTES 3

typedef enum {
	GPON_SW = 0,
	GPON_HW,
	GPON_SW_HW,
} GPON_SW_HW_SELECT_T, GPON_SW_HW_SELECT_t ;

typedef struct XMCS_GponOnuInfo_S {
    __u8  onuId ;
    __u8  state ;
    __u8  sn[GPON_SN_LENS] ;
    __u8  PasswdLength;
	__u8  RegidLength;
    __u8  hexFlag;
    __u8  passwd[GPON_PASSWD_LENS] ;
	__u8  regid[GPON_REG_ID_LENS] ;
    __u8  keyIdx ;
    __u8  key[GPON_ENCRYPT_KEY_LENS] ;
    __u32    actTo1Timer ;
    __u32    actTo2Timer ;
    __u16  omcc ;
    __u8  EmergencyState ;
} GPON_ONU_INFO_t;

typedef struct XMCS_GponGemCounter_S {
    __u64 rxGemFrame ;
    __u64 rxGemPayload ;
    __u64 txGemFrame ;
    __u64 txGemPayload ;
} GEM_STATISTIC_t;

typedef struct XMCS_CounterCfg_S {
    __u8    tcontId;
    __u16   allocId;
    __u16   gemPortId;
    GEM_STATISTIC_t *sta;
} STATISTIC_CFG_t;

struct XMCS_GponTodCfg_S {
    __u32    superframe ;
    __u32    sec ;
    __u32    nanosec ;
} ;
typedef enum{
	SC_PLOAM_POWER_LEVEL_NORMAL,
	SC_PLOAM_POWER_LEVEL_MIN_3DB,
	SC_PLOAM_POWER_LEVEL_MIN_6DB,
	SC_PLOAM_POWER_LEVEL_OTHER
}PLOAM_POWER_LEVEL_T;

typedef struct{
	__u8 numGuardBits;
	__u8 numType1PreambleBits;
	__u8 numType2PreambleBits;
	__u8 numType3PreambleBits;
	__u8 type3PreamblePattern;
	__u8 delimiterData[SC_PLOAM_NUM_DELIMITER_BYTES];
	PLOAM_POWER_LEVEL_T powerLevel;
	__u32 eqd;
}PLOAM_GTC_INFO_T;

#ifdef TCSUPPORT_CPU_EN7521
typedef struct{
    __u16 tcont;
	__u16 alloc_id;
	__u32 tx_counter;
}TCONT_COUNTERS_T;

typedef  struct{
	TCONT_COUNTERS_T counters[CONFIG_GPON_MAX_TCONT];
	__u8 tcont_num;
}ALL_TCONT_COUNTERS_T;
#endif

#endif /* _XPON_GLOBAL_PUBLIC_XMCS_GPON_H_ */

