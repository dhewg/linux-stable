/***************************************************************
Copyright Statement:

This software/firmware and related documentation (EcoNet Software) 
are protected under relevant copyright laws. The information contained herein 
is confidential and proprietary to EcoNet (HK) Limited (EcoNet) and/or 
its licensors. Without the prior written permission of EcoNet and/or its licensors, 
any reproduction, modification, use or disclosure of EcoNet Software, and 
information contained herein, in whole or in part, shall be strictly prohibited.

EcoNet (HK) Limited  EcoNet. ALL RIGHTS RESERVED.

BY OPENING OR USING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY 
ACKNOWLEDGES AND AGREES THAT THE SOFTWARE/FIRMWARE AND ITS 
DOCUMENTATIONS (ECONET SOFTWARE) RECEIVED FROM ECONET 
AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON AN AS IS 
BASIS ONLY. ECONET EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, 
WHETHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, 
OR NON-INFRINGEMENT. NOR DOES ECONET PROVIDE ANY WARRANTY 
WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTIES WHICH 
MAY BE USED BY, INCORPORATED IN, OR SUPPLIED WITH THE ECONET SOFTWARE. 
RECEIVER AGREES TO LOOK ONLY TO SUCH THIRD PARTIES FOR ANY AND ALL 
WARRANTY CLAIMS RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES 
THAT IT IS RECEIVERS SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD 
PARTY ALL PROPER LICENSES CONTAINED IN ECONET SOFTWARE.

ECONET SHALL NOT BE RESPONSIBLE FOR ANY ECONET SOFTWARE RELEASES 
MADE TO RECEIVERS SPECIFICATION OR CONFORMING TO A PARTICULAR 
STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND 
ECONET'S ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE ECONET 
SOFTWARE RELEASED HEREUNDER SHALL BE, AT ECONET'S SOLE OPTION, TO 
REVISE OR REPLACE THE ECONET SOFTWARE AT ISSUE OR REFUND ANY SOFTWARE 
LICENSE FEES OR SERVICE CHARGES PAID BY RECEIVER TO ECONET FOR SUCH 
ECONET SOFTWARE.
***************************************************************/

#include <linux/kernel.h>
#include <linux/timer.h>
#include <asm/tc3162/tc3162.h>

enum {
	__ECNT_CHIP_INIT_XPON_ACTION,
	__ECNT_CHIP_INIT_USB0_ACTION,
	__ECNT_CHIP_INIT_USB1_ACTION,
	__ECNT_CHIP_INIT_PCIE0_ACTION,
	__ECNT_CHIP_INIT_PCIE1_ACTION,

	/* all new action constant should be added above this line */
	__ECNT_CHIP_INIT_ACTION_MAX,
};

enum {
	INTERFACE_PKG_ID = 0,
	INTERFACE_XPON_IDX,
	INTERFACE_USB0_IDX,
	INTERFACE_USB1_IDX,
	INTERFACE_PCIE0_IDX,
	INTERFACE_PCIE1_IDX,

	/* all new IDX should be added above this line */
	INTERFACE_IDX_MAX,
};

typedef struct {
	unsigned int package_id;
	union {
		struct {
			unsigned int isXpon		: 1;
			unsigned int isUsbPort0	: 1;
			unsigned int isUsbPort1	: 1;
			unsigned int isPcie0	: 1;
			unsigned int isPcie1	: 1;
			unsigned int rfu		: 27;
		} field;
		unsigned int raw;
	};
} INTERFACE_INFO;

#define END_PACKAGE_ID	(0xFFFFFFFF)

static void (*__ecnt_init_hook[__ECNT_CHIP_INIT_ACTION_MAX])(void) = {0};
static struct timer_list __ecnt_check_interface_timer;
static int package_id_idx = END_PACKAGE_ID;

static inline void __ecnt_check_interface_all(unsigned long arg)
{
	int i = 0;

	for (i = 0; i< __ECNT_CHIP_INIT_ACTION_MAX; i++)
		if(__ecnt_init_hook[i])
			__ecnt_init_hook[i]();

	mod_timer(&__ecnt_check_interface_timer, jiffies + HZ );

	return;
}

static inline unsigned int get_pkg_info(int pkg_idx, int if_idx)
{
	INTERFACE_INFO if_info[] = {
		/* Add newest package id of IC at here */
		
		/* EN7528 */
		{isEN7528HU,			.field={1, 1, 1, 1, 1}},
		{isEN7528DU,			.field={1, 1, 1, 1, 1}},
		{isEN7561DU,			.field={0, 1, 1, 1, 1}},
		{isEN7526FH_EN7528DU,	.field={1, 1, 1, 1, 0}},
		{isEN7521G_EN7528DU,	.field={1, 1, 1, 0, 0}},
		{isEN7561HU,			.field={0, 1, 1, 1, 1}},

		/* EN7580 */
		{isEN7580GT,	.field={1, 1, 1, 1, 1}},
		{isEN7580ST,	.field={1, 0, 0, 0, 0}},
		{isEN7580GAT,	.field={1, 1, 1, 1, 1}},
		{isEN7565,		.field={0, 1, 1, 1, 1}},

		/* EN7516 */
		{isEN7516G,	.field={0, 1, 1, 1, 1}},

		/* EN7527 */
		{isEN7527G,	.field={1, 1, 1, 1, 1}},
		{isEN7561G,	.field={0, 1, 1, 1, 1}},
		
		/* EN7512 */
		{isEN7512,	.field={0, 1, 0, 1, 0}},
		{isEN7513,	.field={0, 1, 1, 1, 1}},
		{isEN7513G,	.field={0, 1, 1, 1, 1}},
		
		/* EN7521, EN7521FC */
		{isEN7521FCUD,	.field={1, 1, 0, 0, 0}},
		{isEN7521F,		.field={1, 0, 0, 0, 0}},
		{isEN7521S,		.field={1, 0, 0, 0, 0}},
		{isEN7526D,		.field={1, 1, 1, 1, 1}},
		{isEN7526F,		.field={1, 1, 0, 1, 0}},
		{isEN7526G,		.field={1, 1, 1, 1, 1}},
		{isEN7526FT,	.field={1, 1, 0, 1, 0}},
		{isEN7526FP,	.field={1, 1, 0, 1, 0}},
		{isEN7526FT_C,	.field={1, 1, 0, 1, 0}},

		/*must last element*/
	    {END_PACKAGE_ID,		.field={0, 0, 0, 0, 0}}
	};

	switch(if_idx) {
		case INTERFACE_PKG_ID:
			return if_info[pkg_idx].package_id;
			break;
		case INTERFACE_XPON_IDX:
			return if_info[pkg_idx].field.isXpon;
			break;
		case INTERFACE_USB0_IDX:
			return if_info[pkg_idx].field.isUsbPort0;
			break;
		case INTERFACE_USB1_IDX:
			return if_info[pkg_idx].field.isUsbPort1;
			break;
		case INTERFACE_PCIE0_IDX:
			return if_info[pkg_idx].field.isPcie0;
			break;
		case INTERFACE_PCIE1_IDX:
			return if_info[pkg_idx].field.isPcie1;
			break;
		default:
			return END_PACKAGE_ID;
	}
}

static inline int __chip_has_modules(int module)
{
	switch(module) {
		case __ECNT_CHIP_INIT_XPON_ACTION:
			return get_pkg_info(package_id_idx, INTERFACE_XPON_IDX);
		case __ECNT_CHIP_INIT_USB0_ACTION:
			return get_pkg_info(package_id_idx, INTERFACE_USB0_IDX);
		case __ECNT_CHIP_INIT_USB1_ACTION:
			return get_pkg_info(package_id_idx, INTERFACE_USB1_IDX);
		case __ECNT_CHIP_INIT_PCIE0_ACTION:
			return get_pkg_info(package_id_idx, INTERFACE_PCIE0_IDX);
		case __ECNT_CHIP_INIT_PCIE1_ACTION:
			return get_pkg_info(package_id_idx, INTERFACE_PCIE1_IDX);
		default:
			return 0;
	}
}

static inline void __chip_init_check_xpon(void)
{
	#define PHY_CSR_PHYSET3			(0xBFAF0108)
	#define PHY_CSR_PHYSET4			(0xBFAF010C)
	#define PHY_CSR_ANAPWD			(0xBFAF0150)
	#define PHY_CSR_ANATXREG2		(0xBFAF01A4)

	#define PHY_CSR_PHYSET3_PLLRST						(1 << 31)
	#define PHY_CSR_PHYSET3_XP_SRST						(1 << 27)
	#define PHY_CSR_PHYSET4_AUTOK_SQ					(0xfffffffb)
	#define PHY_CSR_ANAPWD_BIAS_PWD						(1 << 9)
	#define PHY_CSR_ANAPWD_CDR_PI_PWD					(1 << 7)
	#define PHY_CSR_ANATXREG2_PON_TX_TXOP_PD_PRE		(1 << 17)
	#define PHY_CSR_ANATXREG2_PON_TX_BEN_TXOP_PD_PRE	(1 << 18)

	__u32 reg_val = 0;

	/*PON PHY PLL & Software Reset*/
	reg_val = ioread32((void __iomem *)(PHY_CSR_PHYSET3));
	reg_val |= PHY_CSR_PHYSET3_PLLRST;
	reg_val |= PHY_CSR_PHYSET3_XP_SRST;
	iowrite32(reg_val, (void __iomem *)(PHY_CSR_PHYSET3));

	/*PON PHY DA_PON_RX_SIGDET_CAL_EN*/
	reg_val = ioread32((void __iomem *)(PHY_CSR_PHYSET4));
	reg_val &= PHY_CSR_PHYSET4_AUTOK_SQ;
	iowrite32(reg_val, (void __iomem *)(PHY_CSR_PHYSET4));

	/*PON PHY DA_PON_RX_CDR_PI_PWD & DA_PON_BIAS_PWD*/
	reg_val = ioread32((void __iomem *)(PHY_CSR_ANAPWD));
	reg_val |= PHY_CSR_ANAPWD_BIAS_PWD;
	reg_val |= PHY_CSR_ANAPWD_CDR_PI_PWD;
	iowrite32(reg_val, (void __iomem *)(PHY_CSR_ANAPWD));

	/*PON PHY RG_PON_TX_TXOP_PD & RG_PON_TX_BEN_TXOP_PD*/
	reg_val = ioread32((void __iomem *)(PHY_CSR_ANATXREG2));
	reg_val |= PHY_CSR_ANATXREG2_PON_TX_TXOP_PD_PRE;
	reg_val |= PHY_CSR_ANATXREG2_PON_TX_BEN_TXOP_PD_PRE;
	iowrite32(reg_val, (void __iomem *)(PHY_CSR_ANATXREG2));

	#undef PHY_CSR_PHYSET3			
	#undef PHY_CSR_PHYSET4			
	#undef PHY_CSR_ANAPWD			
	#undef PHY_CSR_ANATXREG2		

	#undef PHY_CSR_PHYSET3_PLLRST						
	#undef PHY_CSR_PHYSET3_XP_SRST					
	#undef PHY_CSR_PHYSET4_AUTOK_SQ					
	#undef PHY_CSR_ANAPWD_BIAS_PWD					
	#undef PHY_CSR_ANAPWD_CDR_PI_PWD					
	#undef PHY_CSR_ANATXREG2_PON_TX_TXOP_PD_PRE		
	#undef PHY_CSR_ANATXREG2_PON_TX_BEN_TXOP_PD_PRE	

	return;
}

static inline void __chip_init_check_usb0(void)
{
	//TODO: disable USB0
	return;
}

static inline void __chip_init_check_usb1(void)
{
	//TODO: disable USB1
	return;
}

static inline void __chip_init_check_pcie0(void)
{
	//TODO: disable PCIE0
     if(isEN7580ST)
        RegWrite(0xbfaf280c, 0xc0000000);//disable 7580 PCIe port0 phy
	return;
}

static inline void __chip_init_check_pcie1(void)
{
	//TODO: disable PCIE1
     if(isEN7580ST)
        RegWrite(0xbfac080c, 0xc0000000);//disable 7580 PCIe port1 phy
	return;
}

// if chipid is known, return 1, else return 0
static inline int __chipid_in_white_list(void)
{
	int i = 0;

	for(i = 0; get_pkg_info(i, INTERFACE_PKG_ID) != END_PACKAGE_ID; i++) {
		if(get_pkg_info(i, INTERFACE_PKG_ID)) {
			package_id_idx = i;
			return 1;
		}
	}
	
	return 0;
}

/*
 * This is the public API intended to be called by closed-srouce module_init function
 * */
static inline void ecnt_chip_interface_init(void)
{
#if defined(TCSUPPORT_CPU_EN7512) || defined(TCSUPPORT_CPU_EN7521)
	if(!__chipid_in_white_list() )
		panic("unkonw chipid, module load fail!\n");

	if(!__chip_has_modules(__ECNT_CHIP_INIT_XPON_ACTION) )
		__ecnt_init_hook[__ECNT_CHIP_INIT_XPON_ACTION] = __chip_init_check_xpon;
		
	if(!__chip_has_modules(__ECNT_CHIP_INIT_USB0_ACTION) )
		__ecnt_init_hook[__ECNT_CHIP_INIT_USB0_ACTION] = __chip_init_check_usb0;

	if(!__chip_has_modules(__ECNT_CHIP_INIT_USB1_ACTION) )
		__ecnt_init_hook[__ECNT_CHIP_INIT_USB1_ACTION] = __chip_init_check_usb1;

	if(!__chip_has_modules(__ECNT_CHIP_INIT_PCIE0_ACTION) )
		__ecnt_init_hook[__ECNT_CHIP_INIT_PCIE0_ACTION] = __chip_init_check_pcie0;

	if(!__chip_has_modules(__ECNT_CHIP_INIT_PCIE1_ACTION) )
		__ecnt_init_hook[__ECNT_CHIP_INIT_PCIE1_ACTION] = __chip_init_check_pcie1;

	init_timer(&__ecnt_check_interface_timer);
	__ecnt_check_interface_timer.function = __ecnt_check_interface_all;
	__ecnt_check_interface_all(0);
#endif
	return;
}
/*
 * This is the public API intended to be called by closed-srouce module_exit function
 * */
static inline void ecnt_chip_interface_deinit(void)
{
#if defined(TCSUPPORT_CPU_EN7512) || defined(TCSUPPORT_CPU_EN7521)
	del_timer_sync(&__ecnt_check_interface_timer);
#endif
	return;
}


