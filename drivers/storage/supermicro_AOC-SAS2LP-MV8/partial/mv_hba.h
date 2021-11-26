/*Macros within this file are OS independently */
#ifndef __MV_HBA_H__
#define __MV_HBA_H__

#define NEW_CORE_DRIVER		1
#define CORE_NO_RECURSIVE_CALL
#ifndef _OS_LINUX
#define SUPPORT_MODULE_CONSOLIDATE		1
#endif
/* allocate uncached memory multiple times for RAID/Cache module*/
#ifdef _OS_LINUX
#define MULTI_UNCACHE_ALLOC
#endif
/*open this macro to zero sg entry, command header/table memory
 * of each sending request, R/W test on SATA disk easily timeout.*/
#define CORE_ZERO_MEMORY_TEST

#define SUPPORT_TIMER                1
#define SUPPORT_SMALL_TIMER			1
#define SUPPORT_EVENT                1
#define REDUCED_SENSE              1
#define SUPPORT_SCSI_PASSTHROUGH     1
#define SUPPORT_PASS_THROUGH_DIRECT	1
#define REQUEST_TIME_OUT				20		// in multiples of TIMER_INTERVAL, see hba_timer.h

#define MV_MAX_LUN_NUMBER               128
#ifdef SUPPORT_SCSI_PASSTHROUGH
#   define SAT_RETURN_FIS_IN_CDB	1
#   define SUPPORT_VIRTUAL_DEVICE       1
#if !defined (__VMKLNX__)  && !defined(MV_VMK_ESX35)
#   define VIRTUAL_DEVICE_ID            (MV_MAX_TARGET_NUMBER - 1)
#else /*for not use virtual device with vmware*/
#   define VIRTUAL_DEVICE_ID            MV_MAX_TARGET_NUMBER
#endif
#endif /* SUPPORT_SCSI_PASSTHROUGH */
#define MV_MAX_HD_DEVICE_ID                   		MAX_DEVICE_SUPPORTED_PERFORMANCE

/*
 * define USE_NEW_SGTABLE to use the new SG format as defined in
 * "General SG Format" document.
 */
#define USE_NEW_SGTABLE
#ifndef WIN_STORPORT
#if defined(USE_NEW_SGTABLE) && (defined(SOFTWARE_XOR) || defined(CACHE_MODULE_SUPPORT))
#define USE_VIRTUAL_PRD_TABLE           1
#endif
#endif		/* WIN_STORPORT*/

/* support to use NVSRAM memory to save transaction log */
#ifdef SUPPORT_TRANSACTION_LOG
#define SUPPORT_NVSRAM	1
#endif

#endif /*__MV_HBA_H__*/
