/*and by panyong .Flash related macros that are 
 *defined in different places will be moved in this file
 */
#ifndef FLASH_API_H
#define FLASH_API_H



#define MTD_NAME_LEN 25

#define FLASH_IOCTL_READ		(0x01)
#define FLASH_IOCTL_WRITE		(0x02)
#define FLASH_IOCTL_GET_UID		(0x03)
#define FLASH_IOCTL_GET_UID_LEN	(0x04)
#define FLASH_IOCTL_GET_ID		(0x05)
#if (defined(CONFIG_PW_MODEL_VMG1312T20AV1) || defined(CONFIG_PW_MODEL_VMG1302T20AV1))
#define FLASH_IOCTL_READ_NAME		(0x06)
#define FLASH_IOCTL_WRITE_NAME		(0x07)
#endif

enum op_status {
    OUT_OF_SCOPE=10,
	GET_UID_ERROR,
};

struct flash_opt {
    unsigned int    *src;
    unsigned int    *dest;
    unsigned int    bytes;
    unsigned int    start_addr;
    unsigned int    end_addr;
    enum op_status  result;
};
/*定义flashOpt方便上层代码兼容bcm sdk设计，同时保持mtk代码风格不变*/
typedef struct flash_opt   flashOpt;



#ifdef INCLUDE_FLASH_128M
#define FLASH_SIZE          0x8000000
#define BOOT_SIZE     0x20000
#define KERNEL_SIZE   (KERNEL_MAX_SIZE)
#define ROOTFS_SIZE   0x02000000

#if 0
#define ROOM_FILE_OFFSET ((ROOTFS_SIZE + KERNEL_SIZE) * 2 + BOOT_SIZE)
#define ROOM_FILE_SIZE   0x00020000
#else
#define ROOM_FILE_OFFSET BOOT_SIZE
#define ROOM_FILE_SIZE   0x00080000
#endif

#if 0
#define CONFIG_SIZE      0x00040000
#define CONFIG_OFFSET    (ROOM_FILE_OFFSET + ROOM_FILE_SIZE)
#else
#define CONFIG_SIZE      0x00100000
#define CONFIG_OFFSET    (ROOM_FILE_OFFSET + ROOM_FILE_SIZE)
#endif
#if 0
#define KERNEL_2_OFFSET (BOOT_SIZE + KERNEL_SIZE + ROOTFS_SIZE)
#else
#define KERNEL_2_OFFSET (BOOT_SIZE + KERNEL_SIZE + ROOTFS_SIZE+ROOM_FILE_SIZE+CONFIG_SIZE+RADIO_FILE_SIZE)
#endif
#if 0
#define RADIO_FILE_SIZE   0x00020000
#define RADIO_OFFSET     (KERNEL_2_OFFSET + KERNEL_SIZE+ROOTFS_SIZE)
#else
#define RADIO_FILE_SIZE   0x00040000
#define RADIO_OFFSET     (CONFIG_OFFSET + CONFIG_SIZE)
#endif

#define RESERVE_AREA_OFFSET (KERNEL_2_OFFSET +KERNEL_SIZE+ROOTFS_SIZE)
#define RESERVE_AREA_SIZE  (0x07300000 - RESERVE_AREA_OFFSET)




#define BOOTLDR_OFFSET		0x000000
#define KERNEL_OFFSET		(RADIO_OFFSET+RADIO_FILE_SIZE)
#define WIFI2GE2P_SIZE		(RADIO_FILE_SIZE /2) 
#define WIFI5GE2P_SIZE		(RADIO_FILE_SIZE /2) 

/*These parameters are stored in the ROM partition*/
#define SIGN_OFFSET 		0x1000
#define MACADDR_OFFSET		0x2000
#define PIN_OFFSET			0x3000

#ifdef INCLUDE_DECT
#define RFPI_OFFSET			0x4000
#endif
#define DEVICEID_OFFSET		0x5000
#define WLAN_PWD_OFFSET		0x6000
#define WLAN_GUEST_PWD_OFFSET	0x7000


/*These parameters are stored in the MISCCFG partition*/
#define SSL_CA_OFFSET       0x0000
#define SSL_CLIENT_OFFSET   0x9000
#define SSL_KEY_OFFSET      0xA000
#ifdef INCLUDE_FR_CODE
#define FRINFO_OFFSET		0x6000
#endif
#ifdef INCLUDE_TTNET
#define SYSMODE_OFFSET		0x7000
#endif
#define SYSTOOLS_OFFSET     0x8000
#endif


#if defined(INCLUDE_FLASH_8M)
#define RADIO_2G_FLASH_START  	 0x007F0000
#define RADIO_5G_FLASH_START  	 0x007F8000
#define CONFIG_DATA_FLASH_START  0x007E0000
#define MAC_FLASH_START          0x00FDF100

#define FLASH_SECTOR_SIZE 		0x10000
#define FLASH_MAX_RW_SIZE 		FLASH_SECTOR_SIZE

#elif defined(INCLUDE_FLASH_16M)
#define RADIO_2G_FLASH_START  	 0x00FF0000
#define RADIO_5G_FLASH_START  	 0x00FF8000
#define CONFIG_DATA_FLASH_START  0x00FE0000
#define MAC_FLASH_START          0x00FDF100

#define FLASH_SECTOR_SIZE 		0x10000
#define FLASH_MAX_RW_SIZE 		FLASH_SECTOR_SIZE

#elif defined(INCLUDE_FLASH_128M)
#define RADIO_2G_FLASH_START  RADIO_OFFSET
#define RADIO_5G_FLASH_START  RADIO_OFFSET + WIFI2GE2P_SIZE
#define CONFIG_DATA_FLASH_START  CONFIG_OFFSET
#define CONFIG2_DATA_FLASH_START  (CONFIG_OFFSET+FLASH_SECTOR_SIZE*2)
#define MAC_FLASH_START        ROOM_FILE_OFFSET + MACADDR_OFFSET

#define FLASH_SECTOR_SIZE 		0x20000
#define FLASH_MAX_RW_SIZE 		FLASH_SECTOR_SIZE

#endif



//for mac backup
#define SYSBACKUP_MAC_ADDR  (ROOM_FILE_OFFSET+FLASH_SECTOR_SIZE)

// for bootflag
#define BOOT_FLAG_ADDR    (CONFIG_OFFSET+FLASH_SECTOR_SIZE*4)
// for misdata
#define MISCCFG_OFFSET  	(BOOT_FLAG_ADDR+FLASH_SECTOR_SIZE)

//for reboot code
#ifdef INCLUDE_RB_CODE
#define RBINFO_OFFSET		(MISCCFG_OFFSET+FLASH_SECTOR_SIZE)
#endif
/*for boot rom*/
#define TPKERNEL_FLASH_START 			(RADIO_OFFSET+RADIO_FILE_SIZE)
#define TPROOTFS_FLASH_START 			(TPKERNEL_FLASH_START + KERNEL_SIZE)


#ifdef INCLUDE_DUAL_IMAGE
#define TPKERNEL_1_FLASH_START 			KERNEL_2_OFFSET
#define TPROOTFS_1_FLASH_START 			(KERNEL_2_OFFSET + KERNEL_SIZE)
#define ROMFILE_PARTITION_FLASH_START 	ROOM_FILE_OFFSET
#define CONFIG_PARTITION_FLASH_START 	CONFIG_OFFSET
#define RADIO_PARTITION_FLASH_START 	RADIO_OFFSET
#define BOOTFLAG_PARTITION_FLASH_START 	BOOT_FLAG_ADDR
#endif
#define TPLINUX_FLASH_START  			0x0
#define TPLINUX_FLASH_SIZE   			FLASH_SIZE
#define TPRADIO_FLASH_START  			RADIO_2G_FLASH_START
#define TP_MAC_FLASH_OFFSET 			MAC_FLASH_START
/*endf for boot rom*/




#endif
