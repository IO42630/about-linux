#ifndef __MV_PRODUCT_VANIR_H__
#define __MV_PRODUCT_VANIR_H__

/*hardware related*/
#define ODIN_DRIVER                      1
#define SUPPORT_BALDUR			1
#define RUN_AS_PCIE_DRIVER
#define SUPPORT_6G_PHYRATE	1

/*Work around for hardware*/
#ifdef SUPPORT_BALDUR
	#define HOTPLUG_BYTE_COUNT_ERROR_WORKAROUND
	#define TRASH_BUCKET_SIZE 0x400 //1k
	#define NOT_SPINUP_WORKAROUND
//        #define XOR_PI_TABLE                    1
//        #define PRD_DATA_SKIP                   1
//        #define DDR_MEM_SUPPORT                 1
        #define XOR_COALESCE_INT                1
        #define CORE_WIDEPORT_LOAD_BALACE_WORKAROUND
	//#define	DEBUG_PCI_E_ERROR

	/*prepare and reserve slot0 buffer before phy enabled for 
	 *first unassociated data fis transfer. Enable only for Brainaire.(#4885)*/
//	#define COLD_BOOT_DMA_HANG_WORKAROUND

	#define CALIBRATION_CTRL_WA 1
	#define PHY_MODE_WORKAROUND 1
#endif

/*Software workaround and new features*/
#define I2C_NAK20_WORKAROUND			1
#ifndef SUPPORT_MUL_LUN
#define CORE_SCSI_ID_MAP_FOR_NONE_RAID  	1
#endif
//#define SUPPORT_MULTIPATH				1
#ifndef SKIP_INTERNAL_INITIALIZE
#define CORE_SUPPORT_LARGE_REQUEST
#endif
#define CORE_SUPPORT_HBA_PAGE
#define SUPPORT_READ_LOG_EXT
#ifndef RAID_DRIVER
#define HAVE_HW_COMPLIANT_SG
#endif

/*product based raid/xor feature*/
#ifdef RAID_DRIVER
#define SUPPORT_RAID1E                  1
#define HARDWARE_XOR
#ifndef SOFTWARE_XOR
//        #define XOR_LOAD_BALANCE                1
#define XOR_USE_SG_PTR                  1
#endif
/*XOR*/
//#define XOR_LOKI_MISSED_ISR_WORKAROUND          1
//#define LOKI_MISSED_ISR_WORKAROUND              1
//#define CORE_FORCED_ISR_WORKAROUND              1
#endif

/* driver capabilities */
#define MAX_BASE_ADDRESS                6
#ifdef CORE_SUPPORT_LARGE_REQUEST
#ifdef RAID_DRIVER
#define MV_MAX_TRANSFER_SIZE            256*1024 /*can't be larger than 512k*/
#else
#define MV_MAX_TRANSFER_SIZE            4*1024*1024
#endif
#define MAX_SG_ENTRY                    130
#else
#define MV_MAX_TRANSFER_SIZE            (128*1024)
#define MAX_SG_ENTRY                    34
#endif
#define MAX_SG_ENTRY_REDUCED            16
#define MV_MAX_PHYSICAL_BREAK           (MAX_SG_ENTRY - 1)

#if (defined(WIN_NONRAID) || defined(LINUX_NONRAID))
#define MAX_REQUEST_NUMBER_PERFORMANCE	    4096
#ifndef SUPPORT_OEM_PROJECT
#define MAX_REQUEST_PER_LUN_PERFORMANCE		128 // set 128, sometimes SAS disk will task full, if performance ok, can try 64. TBD.
#else
#define MAX_REQUEST_PER_LUN_PERFORMANCE		8 // when supporting max 1024 drives. 
#endif

#else
#define MAX_REQUEST_NUMBER_PERFORMANCE	     1024
#endif
#ifdef SUPPORT_OEM_PROJECT
#define MV_MAX_TARGET_NUMBER            1024
#define MAX_EXPANDER_SUPPORTED		      20
#else
#define MV_MAX_TARGET_NUMBER            128
#define MAX_EXPANDER_SUPPORTED		      10
#endif

/* hardware capabilities */
#define MAX_PM_SUPPORTED                      8
#define MAX_BLOCK_PER_HD_SUPPORTED            8
#define MAX_DEVICE_SUPPORTED_WHQL             8
#define MAX_DEVICE_SUPPORTED_PERFORMANCE      MV_MAX_TARGET_NUMBER
#define MAX_DEVICE_SUPPORTED_RAID             64

/*
define for Flash operation
*/
#define SUPPORT_FLASH_ROM	1
/*support flash update command in core_api*/
#define SUPPORT_FLASH        1
#ifdef SUPPORT_FLASH_ROM
        #define SUPPORT_RMW_FLASH       1
	#define SUPPORT_BOARD_ALARM		1
#endif


/* for PD Page support */
#ifdef RAID_DRIVER
#ifndef SCSI_ID_MAP
#define SUPPORT_PD_PAGE					1
#endif
#ifdef SUPPORT_PD_PAGE
	#define SUPPORT_KEEP_SCSI_ID		1
#endif
#endif	

/* for PD Write Cache Setting saved in Flash (PD Page) */
#define SUPPORT_SAVE_CACHE_IN_FLASH	1
//#define SUPPORT_ERASE_PD_PAGE			1
//#define    SUPPORT_CONFIG_FILE                 1
//#define EXP_ABORT_REQ_DURING_BROADCAST	1

#ifndef _OS_LINUX
#ifdef RAID_DRIVER
/*support NVSRAM memory to save transaction log*/
#define SUPPORT_TRANSACTION_LOG			1
#endif

#else
#define	DISABLE_VSR_IRQ_PHY_TIMEOUT				1
#endif

//#define SUPPORT_I2C                     1
#define SUPPORT_SES                     1
#ifndef SKIP_INTERNAL_INITIALIZE
#define SUPPORT_SGPIO					1
#endif
#ifdef SUPPORT_SGPIO
#define SUPPORT_SGPIO_DATA_IN			1
#define SUPPORT_SGPIO_ACTIVE_LED		1
#endif
//#define SUPPORT_CSMI                    1
#if defined(SUPPORT_I2C)&&defined(SUPPORT_SES)
#define SUPPORT_I2C_SES					1
#endif

#endif/*__MV_PRODUCT_VANIR_H__*/
