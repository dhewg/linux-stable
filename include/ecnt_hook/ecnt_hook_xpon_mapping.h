/***************************************************************
Copyright Statement:

This software/firmware and related documentation (“EcoNet Software”) 
are protected under relevant copyright laws. The information contained herein 
is confidential and proprietary to EcoNet (HK) Limited (“EcoNet”) and/or 
its licensors. Without the prior written permission of EcoNet and/or its licensors, 
any reproduction, modification, use or disclosure of EcoNet Software, and 
information contained herein, in whole or in part, shall be strictly prohibited.

EcoNet (HK) Limited  EcoNet. ALL RIGHTS RESERVED.

BY OPENING OR USING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY 
ACKNOWLEDGES AND AGREES THAT THE SOFTWARE/FIRMWARE AND ITS 
DOCUMENTATIONS (“ECONET SOFTWARE”) RECEIVED FROM ECONET 
AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON AN “AS IS” 
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

#ifndef __LINUX_ENCT_HOOK_XPON_MAPPING_H
#define __LINUX_ENCT_HOOK_XPON_MAPPING_H

/************************************************************************
*               I N C L U D E S
*************************************************************************
*/

#include <ecnt_hook/ecnt_hook.h>
#include <linux/jiffies.h>

/************************************************************************
*               D E F I N E S   &   C O N S T A N T S
*************************************************************************
*/

/* SET function */
#define XPON_MAPPING_SET_CLEAR_HW_NAT_EN                         		0x0001 			     /* void mappingSetClearHwNatEn(int * value)           */

/* Get Function */
#define XPON_MAPPING_GET_DWONSTREAM_UNI                         		0x8001 

/************************************************************************
*               D A T A   T Y P E S
*************************************************************************
*/
#define XPON_MAPPING_NO_API                              (-1)
#define XPON_MAPPING_SUCCESS                             (0)
#define XPON_MAPPING_FAILURE                             (1)

enum ECNT_XPON_MAPPING_SUBTYPE {
    ECNT_XPON_MAPPING_API_TYPE_GET = 0,
    ECNT_XPON_MAPPING_API_TYPE_SET,
};

/************************************************************************
*               M A C R O S
*************************************************************************
*/

/************************************************************************
*               D A T A   D E C L A R A T I O N S
*************************************************************************
*/
typedef struct DS_mapping_uni_s {
    struct sk_buff *skb;
	int				uni;
}DS_mapping_uni_t;

typedef struct xpon_mapping_api_data_s {
    unsigned int    cmd_id    ;  /* [in ]    API command ID      */
    int             ret       ;  /* [out]    API return value    */

    union{                       /* [in|out]                     */
        int                 data            ;
        DS_mapping_uni_t    ds_uni;
    };
}xpon_mapping_api_data_t;


/************************************************************************
*               F U N C T I O N   D E C L A R A T I O N S
                I N L I N E  F U N C T I O N  D E F I N I T I O N S
*************************************************************************
*/    
static inline int CALL_XPON_MAPPING_ENCT_HOOK(xpon_mapping_api_data_t * data, int sub_type)
{
    if(ECNT_HOOK_ERROR == __ECNT_HOOK(ECNT_XPON_MAPPING, sub_type, (struct ecnt_data * )data) ){
        printk("ECNT_HOOK_ERROR occur with cmd_id:0x%x\n", data->cmd_id);
    }

    if(XPON_MAPPING_NO_API == data->ret){
        printk("No such API with type:%d, cmd_id:0x%x\n",sub_type, data->cmd_id);
    }

    return data->ret;
}

static inline int XPON_MAPPING_SET_HWNAT_FLAG_ENCT_HOOK(int value)
{

    xpon_mapping_api_data_t xpon_mapping_data;
    xpon_mapping_data.cmd_id = XPON_MAPPING_SET_CLEAR_HW_NAT_EN;
    xpon_mapping_data.data   = value;
    return CALL_XPON_MAPPING_ENCT_HOOK(&xpon_mapping_data, ECNT_XPON_MAPPING_API_TYPE_SET);
}

static inline int XPON_MAPPING_GET_DS_UNI_ENCT_HOOK(struct sk_buff *skb)
{
	/* 如果uni返回值为-1，则说明匹配失败 */
    xpon_mapping_api_data_t xpon_mapping_data;
    xpon_mapping_data.cmd_id = XPON_MAPPING_GET_DWONSTREAM_UNI;
    xpon_mapping_data.ds_uni.skb = skb;
    CALL_XPON_MAPPING_ENCT_HOOK(&xpon_mapping_data, ECNT_XPON_MAPPING_API_TYPE_GET); 

    return xpon_mapping_data.ds_uni.uni;
}

#endif // __LINUX_ENCT_HOOK_PON_PHY_H


