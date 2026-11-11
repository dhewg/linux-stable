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
#ifndef _ECNT_HOOK_PON_VLAN_H
#define _ECNT_HOOK_PON_VLAN_H

/************************************************************************
*               I N C L U D E S
*************************************************************************
*/

#include <ecnt_hook/ecnt_hook.h>

/************************************************************************
*               D E F I N E S   &   C O N S T A N T S
*************************************************************************
*/
/* SET function */

#define PON_SET_VLAN_START                       0x0001 


#define PON_GET_VLAN_START                       0x8001 
#define PON_GET_VLAN_DOWN_OPT                    0x8002 


#define VLAN_NO_API                              (-1)
#define VLAN_SUCCESS                             (0)
#define VLAN_FAILURE                             (1)

typedef struct{
	int 			port;
    unsigned int 	src_vlan;
    int 			mode;
    int 			vlan;    
} VLAN_Down_opt_t;


typedef struct xpon_van_api_data_s {
    int             api_type  ;  /* [in ]    get or set API      */
    unsigned int    cmd_id    ;  /* [in ]    API command ID      */
    int             ret       ;  /* [out]    API return value    */

    union{                       /* [in|out]                     */
        int                 * data            ;
        VLAN_Down_opt_t     * vlan_down_opt   ;
        void                * raw             ;
    };
}xpon_vlan_api_data_t;

/************************************************************************
*               M A C R O S
*************************************************************************
*/

/************************************************************************
*               D A T A   T Y P E S
*************************************************************************
*/
enum ECNT_XPON_VLAN_SUBTYPE {
    ECNT_XPON_VLAN_API,
};

enum {    
    XPON_VLAN_API_TYPE_GET = 0,    
    XPON_VLAN_API_TYPE_SET,
};

/************************************************************************
*               D A T A   D E C L A R A T I O N S
*************************************************************************
*/

/************************************************************************
*               F U N C T I O N   D E C L A R A T I O N S
                I N L I N E  F U N C T I O N  D E F I N I T I O N S
*************************************************************************
*/
static inline void ECNT_API_XPON_GET_DOWN_OPT(int port,unsigned int src_vlan,int *mode,int *vlan)
{
    xpon_vlan_api_data_t data = {0} ;
	VLAN_Down_opt_t vlan_opt = {0};
    data.cmd_id = PON_GET_VLAN_DOWN_OPT;
    data.api_type = XPON_VLAN_API_TYPE_GET;
	data.vlan_down_opt = &vlan_opt;
	data.vlan_down_opt->port  = port;
    data.vlan_down_opt->src_vlan = src_vlan;
            
    if(ECNT_HOOK_ERROR == __ECNT_HOOK(ECNT_XPON_VLAN, ECNT_XPON_VLAN_API, (struct ecnt_data * )&data) ){
        printk("ECNT_HOOK_ERROR occur. %s:%d\n", __FUNCTION__, __LINE__);
        return;
    }

    *mode = data.vlan_down_opt->mode;
    *vlan = data.vlan_down_opt->vlan;

}

#endif /*_ECNT_HOOK_EVENT_H*/
