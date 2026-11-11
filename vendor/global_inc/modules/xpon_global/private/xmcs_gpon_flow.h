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


#ifndef _XPON_GLOBAL_PRIVATE_XMCS_GPON_FLOW_H_
#define _XPON_GLOBAL_PRIVATE_XMCS_GPON_FLOW_H_

#include <linux/types.h>
#include "../public/xmcs_gpon_flow.h"


#define GLOBAL_GPON_IOC_DEV_NAME			"/dev/gpon_flow"
#define GLOBAL_GPON_IOC_NAME				"gpon_flow"
#define GLOBAL_GPON_IOC_MAGIC 				'w'
#define GLOBAL_GPON_MAJOR 					184    

#define GLOBAL_GPON_IOC_OMCI_CMD 			_IOW(GLOBAL_GPON_IOC_MAGIC, 0, unsigned char)

#define GLOBAL_GPON_IOC_MAX_NR				1

#define GPON_FLOW_MAX_CMD_ARG_NUM			4
#define GPON_FLOW_MAX_CMD_ARG_LEN			32
#define GPON_FLOW_MAX_CMD_LEN				((GPON_FLOW_MAX_CMD_ARG_NUM)*(GPON_FLOW_MAX_CMD_ARG_LEN + 1))

#ifndef MT_OMCI_MSG_TYPE_CREAT
#define MT_OMCI_MSG_TYPE_CREAT				4
#endif

#ifndef MT_OMCI_MSG_TYPE_DELETE
#define MT_OMCI_MSG_TYPE_DELETE				6
#endif

#ifndef MT_OMCI_MSG_TYPE_SET
#define MT_OMCI_MSG_TYPE_SET				8
#endif

#ifndef MT_OMCI_MSG_TYPE_MIB_RESET
#define MT_OMCI_MSG_TYPE_MIB_RESET			15
#endif

#define OMCI_FLOW_MAX_MAP_NUM    512

#define ME_ATTR_MASK_CALCULATION(index) (1 << (16 - (index)))


/* 9.2.2
 * T-CONT 
 */
#define ME_T_CONT_ATTR_PORT_ID         		ME_ATTR_MASK_CALCULATION(1)
#define ME_T_CONT_ATTR_DIRECTION       		ME_ATTR_MASK_CALCULATION(3)
	
#define ME_T_CONT_ATTR_ALL  		ME_T_CONT_ATTR_PORT_ID   | \
									ME_T_CONT_ATTR_DIRECTION
typedef struct meTcont_raw_s
{
	__u16 instID;
	__u16 allocID;
	__u8 policy;
}meTcont_raw_t, * meTcont_raw_p;


/* 9.2.3
 * GEM port network CTP 
 */
#define ME_GEM_CTP_ATTR_PORT_ID             	ME_ATTR_MASK_CALCULATION(1)
#define ME_GEM_CTP_ATTR_TCONT_ID            	ME_ATTR_MASK_CALCULATION(2)
#define ME_GEM_CTP_ATTR_DIRECTION           	ME_ATTR_MASK_CALCULATION(3)
#define ME_GEM_CTP_ATTR_TRAFFIC_MGR_PTR_UP   	ME_ATTR_MASK_CALCULATION(4)
#define ME_GEM_CTP_ATTR_TRAFFIC_DESC_PTR_UP  	ME_ATTR_MASK_CALCULATION(5)
#define ME_GEM_CTP_ATTR_TRAFFIC_DESC_PTR_DOWN	ME_ATTR_MASK_CALCULATION(7)

#define ME_GEM_CTP_ATTR_ALL  	  ME_GEM_CTP_ATTR_PORT_ID   | \
                                  ME_GEM_CTP_ATTR_TCONT_ID  | \
                                  ME_GEM_CTP_ATTR_DIRECTION | \
								  ME_GEM_CTP_ATTR_TRAFFIC_MGR_PTR_UP  | \
								  ME_GEM_CTP_ATTR_TRAFFIC_DESC_PTR_UP | \
								  ME_GEM_CTP_ATTR_TRAFFIC_DESC_PTR_DOWN
                                 
typedef enum{
 GEM_CTP_DIRECTION_UPSTREAM =  1,
 GEM_CTP_DIRECTION_DOWNSTREAM   ,
 GEM_CTP_DIRECTION_BIDIRECTION  ,
} gemCtpDir_t;

typedef struct meGemCtp_raw_s
{
	__u16 instID;
	__u16 portID;
    __u16 tcontID;
    gemCtpDir_t  direction; /* gem port direction */
    __u16 trafficMgrPtrUp;
    __u16 TDProPtrUp;
    __u16 TDProPtrDown;
}meGemCtp_raw_t, * meGemCtp_raw_p;


/* 9.2.4
 * GEM Interworking termination point
 */
#define ME_GEM_IWTP_ATTR_GEM_CTP_POINTER    ME_ATTR_MASK_CALCULATION(1)

#define ME_GEM_IWTP_ATTR_ALL     		ME_GEM_IWTP_ATTR_GEM_CTP_POINTER

typedef struct meGemIwTp_raw_s
{
	__u16 instID;
    __u16 gemCTPInstID;
}meGemIwTp_raw_t, * meGemIwTp_raw_p;


/* 9.2.5
 * Multicast GEM interwork termination point
 */
#define ME_MULTI_GEM_IWTP_ATTR_GEM_CTP_POINTER    ME_ATTR_MASK_CALCULATION(1)

#define ME_MULTI_GEM_IWTP_ATTR_ALL     		ME_MULTI_GEM_IWTP_ATTR_GEM_CTP_POINTER

typedef struct meMultiGemIwTp_raw_s
{
	__u16 instID;
    __u16 GemCTPInstID;
}meMultiGemIwTp_raw_t, * meMultiGemIwTp_raw_p;

/* 9.2.10
 * Priority Queue
 */
#define ME_PRI_Q_ATTR_RELATED_PORT    				ME_ATTR_MASK_CALCULATION(6)
#define ME_PRI_Q_ATTR_TRAFFIC_SCHEDULER_POINTER    	ME_ATTR_MASK_CALCULATION(7)
#define ME_PRI_Q_ATTR_WEIGHT    					ME_ATTR_MASK_CALCULATION(8)

#define ME_PRI_Q_ATTR_ALL 		ME_PRI_Q_ATTR_RELATED_PORT   | \
                                ME_PRI_Q_ATTR_TRAFFIC_SCHEDULER_POINTER  | \
                                ME_PRI_Q_ATTR_WEIGHT

typedef struct mePriorityQ_raw_s
{
	__u16 instID;
    __u32 relatedPort;
    __u16 tsPointer;
    __u8 weight;
}mePriorityQ_raw_t, * mePriorityQ_raw_p;

/* 9.2.11
 * Traffic  Scheduler
 */
#define ME_TS_ATTR_T_CONT_POINTER    			ME_ATTR_MASK_CALCULATION(1)
#define ME_TS_ATTR_TRAFFIC_SCHEDULER_POINTER    ME_ATTR_MASK_CALCULATION(2)
#define ME_TS_ATTR_POLICY_POINTER    			ME_ATTR_MASK_CALCULATION(3)
#define ME_TS_ATTR_WEIGHT_POINTER    			ME_ATTR_MASK_CALCULATION(4)

#define ME_TS_ATTR_ALL 			ME_TS_ATTR_T_CONT_POINTER   | \
                                ME_TS_ATTR_TRAFFIC_SCHEDULER_POINTER  | \
								ME_TS_ATTR_POLICY_POINTER  | \
                                ME_TS_ATTR_WEIGHT_POINTER

typedef struct meTS_raw_s
{
	__u16 instID;
    __u16 tcontPointer;
    __u16 tsPointer;
    __u8 policy;
    __u8 weight;
}meTS_raw_t, * meTS_raw_p;


/* 9.2.12
 * Traffic  Descriptor
 */
#define ME_TD_ATTR_CIR    			ME_ATTR_MASK_CALCULATION(1)
#define ME_TD_ATTR_PIR   			ME_ATTR_MASK_CALCULATION(2)
#define ME_TD_ATTR_CBS    			ME_ATTR_MASK_CALCULATION(3)
#define ME_TD_ATTR_PBS    			ME_ATTR_MASK_CALCULATION(4)
#define ME_TD_ATTR_COLR_MODE		ME_ATTR_MASK_CALCULATION(5)
#define ME_TD_ATTR_ING_COLR_MODE   	ME_ATTR_MASK_CALCULATION(6)
#define ME_TD_ATTR_EG_COLR_MODE    	ME_ATTR_MASK_CALCULATION(7)
#define ME_TD_ATTR_METER_TYPE		ME_ATTR_MASK_CALCULATION(8)

#define ME_TD_ATTR_ALL 			ME_TD_ATTR_CIR   | \
                                ME_TD_ATTR_PIR  | \
								ME_TD_ATTR_CBS  | \
								ME_TD_ATTR_PBS	| \
								ME_TD_ATTR_COLR_MODE	| \
								ME_TD_ATTR_ING_COLR_MODE	| \
								ME_TD_ATTR_EG_COLR_MODE	| \
                                ME_TD_ATTR_METER_TYPE

typedef struct meTD_raw_s
{
	__u16 instID;
    __u32 cir;
    __u32 pir;
    __u32 cbs;
    __u32 pbs;
    __u8 colourMode;
    __u8 ingressColourMode;
    __u8 egressColourMode;
    __u8 meterType;
}meTD_raw_t, * meTD_raw_p;


/* 9.3.1
 * MBSP: Mac bridge service profile
 */

#define ME_MBSP_ATTR_UNI_BRIDGE_ENABLE      ME_ATTR_MASK_CALCULATION(3)
#define ME_MBSP_ATTR_HELLO_TIME             ME_ATTR_MASK_CALCULATION(6)
#define ME_MBSP_ATTR_DYN_FILTER_AGING_TIME  ME_ATTR_MASK_CALCULATION(10)

#define ME_MBSP_ATTR_ALL ( ME_MBSP_ATTR_UNI_BRIDGE_ENABLE     | \
                           ME_MBSP_ATTR_HELLO_TIME            | \
                           ME_MBSP_ATTR_DYN_FILTER_AGING_TIME   )
                         
typedef struct meMbsp_raw_s
{
	__u16 instID;
    __u8  uniBridgingEnable;
    __u16 helloTime;
    __u16 dynFilterAgingTime;
}meMbsp_raw_t, * meMbsp_raw_p;


/* 9.3.4
 * MBPCD: Mac bridge port config data
 */
#define ME_MBPCD_ATTR_BRIGE_ID				ME_ATTR_MASK_CALCULATION(1)
#define ME_MBPCD_ATTR_TP_TYPE				ME_ATTR_MASK_CALCULATION(3)
#define ME_MBPCD_ATTR_TP_POINTER			ME_ATTR_MASK_CALCULATION(4)

#define ME_MBPCD_ATTR_ALL  ( ME_MBPCD_ATTR_BRIGE_ID     | \
                             ME_MBPCD_ATTR_TP_TYPE      | \
                             ME_MBPCD_ATTR_TP_POINTER      )
typedef struct meMbpcd_raw_s
{
	__u16 	instID;
	__u16	bridgeID;
	__u8 	tpType;
	__u16	tpPointer;
}meMbpcd_raw_t, * meMbpcd_raw_p;

/* 9.3.10
 * IEEE 802.1p Mapper Service Profile
 */
#define ME_8021_MAPPER_ATTR_TP_POINTER        ME_ATTR_MASK_CALCULATION(1)
#define ME_8021_MAPPER_ATTR_TP_GEMIWTP_P0     ME_ATTR_MASK_CALCULATION(2)
#define ME_8021_MAPPER_ATTR_TP_GEMIWTP_P1     ME_ATTR_MASK_CALCULATION(3)
#define ME_8021_MAPPER_ATTR_TP_GEMIWTP_P2     ME_ATTR_MASK_CALCULATION(4)
#define ME_8021_MAPPER_ATTR_TP_GEMIWTP_P3     ME_ATTR_MASK_CALCULATION(5)
#define ME_8021_MAPPER_ATTR_TP_GEMIWTP_P4     ME_ATTR_MASK_CALCULATION(6)
#define ME_8021_MAPPER_ATTR_TP_GEMIWTP_P5     ME_ATTR_MASK_CALCULATION(7)
#define ME_8021_MAPPER_ATTR_TP_GEMIWTP_P6     ME_ATTR_MASK_CALCULATION(8)
#define ME_8021_MAPPER_ATTR_TP_GEMIWTP_P7     ME_ATTR_MASK_CALCULATION(9)
#define ME_8021_MAPPER_ATTR_UNMARK_FRAME_OPT  ME_ATTR_MASK_CALCULATION(10)
#define ME_8021_MAPPER_ATTR_DSCP2PBIT_MAP     ME_ATTR_MASK_CALCULATION(11)
#define ME_8021_MAPPER_ATTR_DEFAULT_PBIT      ME_ATTR_MASK_CALCULATION(12)
#define ME_8021_MAPPER_ATTR_TP_TYPE           ME_ATTR_MASK_CALCULATION(13)

#define ME_8021_MAPPER_ATTR_TP_GEMIWTP_PBIT(pbit)     ME_ATTR_MASK_CALCULATION((pbit)+2)


#define ME_8021P_MAPPER_ATTR_ALL     (  ME_8021_MAPPER_ATTR_TP_TYPE          | \
                                        ME_8021_MAPPER_ATTR_TP_POINTER       | \
                                        ME_8021_MAPPER_ATTR_TP_GEMIWTP_P0    | \
                                        ME_8021_MAPPER_ATTR_TP_GEMIWTP_P1    | \
                                        ME_8021_MAPPER_ATTR_TP_GEMIWTP_P2    | \
                                        ME_8021_MAPPER_ATTR_TP_GEMIWTP_P3    | \
                                        ME_8021_MAPPER_ATTR_TP_GEMIWTP_P4    | \
                                        ME_8021_MAPPER_ATTR_TP_GEMIWTP_P5    | \
                                        ME_8021_MAPPER_ATTR_TP_GEMIWTP_P6    | \
                                        ME_8021_MAPPER_ATTR_TP_GEMIWTP_P7    | \
                                        ME_8021_MAPPER_ATTR_DSCP2PBIT_MAP    | \
                                        ME_8021_MAPPER_ATTR_UNMARK_FRAME_OPT | \
                                        ME_8021_MAPPER_ATTR_DEFAULT_PBIT       )

typedef struct me8021pMapper_raw_s
{
	__u16 instID;
	__u16 tpPointer;
    __u16 pbit_GemIWTP[8];
	__u8  unmark_frame_opt;  /*0: derive from DSCP; 1: use default pbit*/
    __u8  dscp2pbitMap[24];
	__u8  defaultPbit;
	__u8  tpType;
}me8021pMapper_raw_t, * me8021pMapper_raw_p;


/* 9.3.11
 * VTFD: Vlan tagging filter data
 */
#define ME_VTFD_ATTR_VLAN_FILTER_LIST		ME_ATTR_MASK_CALCULATION(1)
#define ME_VTFD_ATTR_FORWARD_OPERATION		ME_ATTR_MASK_CALCULATION(2)
#define ME_VTFD_ATTR_VLAN_FILTER_NUMS		ME_ATTR_MASK_CALCULATION(3)

#define ME_VTFD_ATTR_ALL     		ME_VTFD_ATTR_VLAN_FILTER_LIST | \
                             		ME_VTFD_ATTR_VLAN_FILTER_NUMS | \
                             		ME_VTFD_ATTR_FORWARD_OPERATION

typedef struct meVtfd_raw_s
{
	__u16 	instID;
	__u16 	vlanFilterList[12];
	__u8 	forwardOperation;
	__u8 	vlanFilterNums;
}meVtfd_raw_t,* meVtfd_raw_p;


/* 9.3.12
 * VTOCD: Vlan Tagging Operation Configuration Data
 */
typedef struct meVtocd_raw_s
{
	__u16 instID;
} meVtocd_raw_t, * meVtocd_raw_p;


/* 9.3.13
 * EVTOCD: Extended Vlan Tagging Operation Configuration Data 
 */
typedef struct meEvtocd_raw_s
{
	__u16 instID;
} meEvtocd_raw_t, * meEvtocd_raw_p;


/* 9.5.1
 * PPTP Eth UNI:  Physical path termination point Ethernet UNI
 */
typedef struct mePptpEthUni_raw_s
{
	__u16 	instID;
}mePptpEthUni_raw_t, * mePptpEthUni_raw_p;

/* 9.5.5
 * VEIP:  virtual ethernet interface point
 */
typedef struct meVeip_raw_s
{
	__u16 	instID;
}meVeip_raw_t, * meVeip_raw_p;



/*****************************************************************************/

typedef enum {
	FLOW_IMPORT = 0,
	FLOW_CFG_DATA,
	FLOW_DBG_CMD,
	FLOW_CLEAN_ALL,
}FlowAction_t;

typedef struct FlowRawData_s{
    __u8  msgType;
    __u16 classId;
    __u16 instId;
    __u16 attrMask;
    void * data;
}FlowRawData_t, *FlowRawData_p;


typedef struct FlowCfgData_s{
	meTcont_raw_t tcont_data;
    mePriorityQ_raw_t  pq_data;
    int max_tcont_num;
    int max_eth_num;
    int tcont_slot;
    int eth_slot;
    __u8 trafficMgrOp;
}FlowCfgData_t, *FlowCfgData_p;


typedef struct FlowIoctlData_s
{
	FlowAction_t option_flag;//0:get 1:set 2:del 3: clean 4:clean all 5:show

	char *cmd_data[GPON_FLOW_MAX_CMD_ARG_NUM];
	FlowCfgData_t *cfg_data;
	FlowRawData_t omci_msg;
}FlowIoctlData_t, *FlowIoctlData_p;





#endif /* _XPON_GLOBAL_PRIVATE_XMCS_GPON_FLOW_H_ */
