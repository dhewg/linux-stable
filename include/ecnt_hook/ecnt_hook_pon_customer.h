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
#ifndef _ECNT_HOOK_PON_CUSTOMER_H
#define _ECNT_HOOK_PON_CUSTOMER_H

/************************************************************************
*               I N C L U D E S
*************************************************************************
*/

#include <ecnt_hook/ecnt_hook.h>
#include <ecnt_hook/ecnt_hook_pon_mac.h>

/************************************************************************
*               D E F I N E S   &   C O N S T A N T S
*************************************************************************
*/


typedef enum ECNT_XPON_CUSTOMER_CALLBACKS {
	ECNT_XPON_CALLBACK_VLAN_OP_TX,
	ECNT_XPON_CALLBACK_DSCP_OP_TX,
	ECNT_XPON_CALLBACK_VLAN_ADD_RX,
	ECNT_XPON_CALLBACK_VLAN_REMOVE_TX,
	ECNT_XPON_CALLBACK_VLAN_TRANS_TX,
	ECNT_XPON_CALLBACK_SKB_VLAN_PASER,
	ECNT_XPON_CALLBACK_VLAN_FILTER_HANDLE,
	ECNT_XPON_CALLBACK_MULTICAST_RX_DATA,
	ECNT_XPON_CALLBACK_PHY_EVENT,
	ECNT_XPON_CALLBACK_XMCS_CHECK_EVENT_VALID,
	ECNT_XPON_CALLBACK_SET_EMERGENCE_STATE,
	ECNT_XPON_CALLBACK_FH_TX_POWER_HANDLE,
	ECNT_XPON_CALLBACK_SET_ONU_ID,
	ECNT_XPON_CALLBACK_SET_OMCC_ID,
	ECNT_XPON_CALLBACK_SET_PHY_EVENT_HANDLER,
    ECNT_XPON_CALLBACK_MAX_NUM,
}XPON_CUSTOMER_Callbacks_t;

typedef enum {    
	XPON_CUSTOMER_API_CALLBACK_RESET = 0,    
	XPON_CUSTOMER_API_CALLBACK_REGISTER,
	XPON_CUSTOMER_API_CALLBACK_PHY_EVENT_HANDLER,
	XPON_CUSTOMER_API_MAX_NUM,
}XPON_Api_t;


/************************************************************************
*               M A C R O S
*************************************************************************
*/

/************************************************************************
*               D A T A   T Y P E S
*************************************************************************
*/

typedef struct{
	XPON_CUSTOMER_Callbacks_t	callback_id;
	void*	callback_fn; 
} XPON_CALLBACK_Info_t;

typedef struct ECNT_XPON_CUSTOMER_Data {
	XPON_Api_t function_id;	/* need put at first item */
	unsigned int    cmd_id;
	int eventtype;
	int retValue;
	
	union {
		XPON_CALLBACK_Info_t	callback;
	} xpon_customer_private;
}ECNT_XPON_CUSTOMER_Data_t;

/************************************************************************
*               D A T A   D E C L A R A T I O N S
*************************************************************************
*/

/************************************************************************
*               F U N C T I O N   D E C L A R A T I O N S
                I N L I N E  F U N C T I O N  D E F I N I T I O N S
*************************************************************************
*/

/******************************************************************************
 Descriptor:    It's used to reset all callback function poiner inner XPON module.
 Input Args:    void.
 Ret Value: success: ECONET_E_SUCCESS
                       fail: ECONET_E_FAIL
******************************************************************************/
static inline int ECNT_XPON_CUSTOMER_CALLBACK_RESET(void)
{
	int ret=0;
	ECNT_XPON_CUSTOMER_Data_t data = {0} ;
	data.function_id = XPON_CUSTOMER_API_CALLBACK_RESET;

	ret = __ECNT_HOOK(ECNT_XPON_MAC, ECNT_XPON_CUSTOMER_HOOK, (struct ecnt_data * )&data);

	if(ret != ECNT_HOOK_ERROR){
		return data.retValue;
	}
	else{
		printk("ECNT_HOOK_ERROR occur. %s:%d\n", __FUNCTION__, __LINE__);
		return ECNT_HOOK_ERROR;
	}

}

/******************************************************************************
 Descriptor:    It's used to register a specific callback function into xpon module.
 Input Args:    XPON_CALLBACK_Info_t: it contains a callback function id and a callback function pointer.
 Ret Value: success: ECONET_E_SUCCESS
                       fail: ECONET_E_FAIL
******************************************************************************/
static inline int ECNT_XPON_CUSTOMER_CALLBACK_REGISTER(XPON_CALLBACK_Info_t* callback)
{
	int ret=0;
	ECNT_XPON_CUSTOMER_Data_t data = {0} ;
	data.function_id = XPON_CUSTOMER_API_CALLBACK_REGISTER;
	data.xpon_customer_private.callback.callback_id = callback->callback_id;
	data.xpon_customer_private.callback.callback_fn = callback->callback_fn;

	ret = __ECNT_HOOK(ECNT_XPON_MAC, ECNT_XPON_CUSTOMER_HOOK, (struct ecnt_data * )&data);

	if(ret != ECNT_HOOK_ERROR){
		return data.retValue;
	}
	else{
		printk("ECNT_HOOK_ERROR occur, callback_id:%d. %s:%d\n", callback->callback_id, __FUNCTION__, __LINE__);
		return ECNT_HOOK_ERROR;
	}

}

static inline int ECNT_XPON_CUSTOMER_PHY_EVENT_HANDLER(uint cmd_id, int eventtype)
{
	int ret=0;
	ECNT_XPON_CUSTOMER_Data_t data = {0};
	data.function_id = XPON_CUSTOMER_API_CALLBACK_PHY_EVENT_HANDLER;

	data.cmd_id = cmd_id;
	data.eventtype = eventtype;
	
	ret = __ECNT_HOOK(ECNT_XPON_MAC, ECNT_XPON_CUSTOMER_HOOK, (struct ecnt_data * )&data);

	if(ret != ECNT_HOOK_ERROR){
		return data.retValue;
	}
	else{
		printk("ECNT_HOOK_ERROR occur. %s:%d\n",  __FUNCTION__, __LINE__);
		return ECNT_HOOK_ERROR;
	}
}
#endif /*_ECNT_HOOK_PON_CUSTOMER_H*/
