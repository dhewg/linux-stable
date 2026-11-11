#ifndef __TP_PARTITION_H__
#define __TP_PARTITION_H__

/**************************************************************************************************/
/*                                           DEFINES                                              */
/**************************************************************************************************/


/************************************* partition size defines *************************************/
/****** 7516 nor flash layout ******/
/*
 * boot
 * romfile
 * kernel
 * rootfs
 * kernel_slave
 * rootfs_slave
 * reserve
 */

#define MTD_MISC_SIZE       0x10000
#define MTD_BOOT_SIZE		0x20000
#define MTD_ROMFILE_SIZE	0x10000
#define MTD_KERNEL_SIZE     0x180000
#define MTD_ROOTFS_SIZE     0x220000
#define MTF_FLASH_SIZE      0x800000
#ifdef TCSUPPORT_REMOTE_BOARD
#define MTD_IMAGE_SIZE      0x7e0000
#else
#define MTD_IMAGE_SIZE      0x3e0000
#endif
#define MTD_OFS_BFLAG       MTD_BOOT_SIZE
#define MTD_BFLAG_SIZE      0x2
#define MTD_OFS_MISC		MTD_OFS_BFLAG
/************************************* partition offset defines ***********************************/
#define MTD_OFS_KERNEL		(MTD_BOOT_SIZE + MTD_ROMFILE_SIZE)
#define MTD_OFS_ROOTFS		(MTD_BOOT_SIZE + MTD_OFS_KERNEL + MTD_KERNEL_SIZE)

#define MTD_OFS_KERNEL2		(MTD_BOOT_SIZE + MTD_ROMFILE_SIZE + MTD_IMAGE_SIZE)
#define MTD_OFS_ROOTFS2		(MTD_IMAGE_SIZE + MTD_KERNEL_SIZE)




/************************************** block index defines ***************************************/


/************************************** block offset defines **************************************/

/************************************* offsets in other block *************************************/


/***************************************** for image tag ******************************************/
/* 
 * Dual image flag	
 */
#define TP_IMAGE_MASTER		0
#define TP_IMAGE_SLAVE		1

/************************************** type fs mount point ***************************************/

typedef struct
{
	struct
	{
		unsigned char is_committed;		
		unsigned char is_active;		
		unsigned char is_valid;
	}image[2];
	unsigned char active_flag;
	unsigned char csum;
}IMG_BOOT_INFO;

#endif /* __TP_PARTITION__ */
