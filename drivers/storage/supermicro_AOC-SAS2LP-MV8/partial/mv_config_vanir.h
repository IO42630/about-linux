#ifndef __MV_CONFIG_VANIR_H__
#define __MV_CONFIG_VANIR_H__

#define VANIR_PRODUCT

/* driver configuration */
#define mv_driver_name   "mv94xx"
#define mv_product_name  "VANIR"

/*Driver Version for Command Line Interface Query.*/
#define VER_MAJOR           4
#define VER_MINOR        0
#define VER_OEM        	0
#ifdef RAID_DRIVER
#define VER_BUILD        1411
#define VER_TEST         ""
#else
#define VER_BUILD        1544
#define VER_TEST         "N"
#endif

#define 	MV_DEBUG	1
#ifdef MV_DEBUG
//#define	STRONG_DEBUG	1
#endif

#ifndef RAID_DRIVER
#define LINUX_NONRAID
#define SUPPORT_STAGGERED_SPIN_UP			1
//#define	SUPPORT_OEM_PROJECT		1	//Enable it only OEM project, generic driver should disable it.
#ifndef SUPPORT_OEM_PROJECT
/*Temp disable DIF support. If a DIF type 2 disk is attached the  VARLEN CDB must also be supported*/
#define		SUPPORT_VARLEN_CDB	1
#define		SUPPORT_DIF	1
//#define		USE_OS_TIMEOUT_VALUE 1
#endif
#endif

//#define 	SUPPORT_IO_DELAY	1
//#define	DEBUG_EXPANDER			1
#ifdef SUPPORT_OEM_PROJECT
#define	SKIP_INTERNAL_INITIALIZE	1
#define 	ENABLE_HARD_RESET_EH		1
#endif

#define SUPPORT_ENHANCED_EH	1
#ifdef SUPPORT_ENHANCED_EH
/* This workaround can recovered all disks drop issue with AIC expanders.
   Temp disable it, if one real bad disk exists, which can't be recoverd,
   we shouldn't reset all expander port. This will block IO on all devices.*/
//#define SUPPORT_PORT_RESET_FOR_STP	1
#endif

#ifndef MV_VMK_ESX35
#if (!defined(RAID_DRIVER) && !defined(__VMKLNX__))
#define SUPPORT_MUL_LUN					1
#endif
#endif

#define SUPPORT_SG_RESET 1

#define SUPPORT_LUIGI	1
#ifdef SUPPORT_LUIGI
#ifndef RAID_DRIVER
#define USE_OS_TIMEOUT_VALUE	1
#endif
#endif

#if defined(PRODUCTNAME_VANIR)
#include "mv_product_vanir.h"
#elif defined(PRODUCTNAME_VANIRLITES)
#include "mv_product_vanirlites.h"
#endif

#include "mv_hba.h"
#ifdef RAID_DRIVER
#include "mv_raid.h"
#endif

#define SUPPORT_VU_CMD				1
#ifdef SUPPORT_EXPANDER
#define ASIC_WORKAROUND_WD_TO_RESET
#endif
//#define SWAP_VANIR_PORT_FOR_LENOVO
#ifndef RAID_DRIVER
#define FIX_SCSI_ID_WITH_PHY_ID
#endif

#ifdef FIX_SCSI_ID_WITH_PHY_ID
	#define PORT_NUMBER 8
#endif
#include "mv_linux.h"

#endif/*__MV_CONFIG_VANIR_H__*/
