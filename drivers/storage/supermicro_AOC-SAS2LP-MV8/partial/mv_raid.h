#ifndef __MV_RAID_H__
#define __MV_RAID_H__

#   define BGA_SUPPORT                     1
//#   define SUPPORT_MP					   1
#   define SUPPORT_FREE_POLICY             1
//#   define SUPPORT_SRL                     1
//#   define SUPPORT_MIGRATION               1
//#   define SUPPORT_RAID_LEVEL_RAID6        1
#   define SUPPORT_DUAL_DDF                0
//#   define SUPPORT_RAID6                   1	/* defined in makefile*/
#      ifdef SUPPORT_RAID6
#         define USE_MATH_LIBARY           1
#         define SUPPORT_READ_MODIFY_WRITE 1
#         define RAID_USE_64K_SU           1
#         define RAID5_FAST_REBUILD
#ifndef SOFTWARE_XOR
#         define RAID6_MULTIPLE_PARITY		/* new feature */
#         define RAID6_HARDWARE_XOR
#endif
#      endif /* SUPPORT_RAID6 */
#   define MV_MIGRATION_RESERVED_SPACE_V1  2048
#   define MV_MIGRATION_RESERVED_SPACE_V2  32768 //16MB	// SECTORS
#   define MV_MIGRATION_SHIFT_SPACE        2048  //1MB	// SECTORS
#   define PERFORMANCE_WHQL_SWITCH


/* New features in RAID  */
#ifndef SOFTWARE_XOR
#   define USE_NEW_GF_TABLE				1
#   define USE_NEW_RAID_MATRIX			1       //Note: NEW_RAID_MATRIX must be used with NEW_GF_TABLE
#endif

//#   define _FOREGROUND_INIT				1
//#   define NEW_MEM_ALLOC			1
//#   define SUPPORT_DISK_GRP			1
#ifdef SUPPORT_DISK_GRP
//#   define SUPPORT_PD_PATH			1
//#   define _BGA_COPY_BACK			1
/* support backward compatibility (odin to loki)*/
//#define SUPPORT_BACKWARD_COMPATIBLE	1
#ifdef SUPPORT_BACKWARD_COMPATIBLE
#define SUPPORT_IMPORT					1
#endif /* SUPPORT_BACKWARD_COMPATIBLE */
#endif	/* SUPPORT_DISK_GRP */

#if defined(SUPPORT_RAID6)
#ifndef SUPPORT_DEDICATED_SPARE
#define SUPPORT_DEDICATED_SPARE
#endif
//#   define SUPPORT_REBUILD_WITH_MULTI_SPARE		1

#   define SUPPORT_RAID_MP			1
#endif /*SUPPORT_RAID6*/

/* for Spin Down Disks */
//#   define START_SAS_IF_STOPPED				1
#define	RAID_SPIN_DOWN_ALL_PD			1

#ifdef _BGA_COPY_BACK
	#if !defined(SUPPORT_PD_PATH) || (SUPPORT_PD_PATH==0)
		#error "Must define SUPPORT_PD_PATH for CopyBack."
	#endif
#endif

#	define ALLOCATE_SENSE_BUFFER		1
#	define RAID_ERROR_HANDLING		1	/* New RAID module error handling implementation */

#ifdef RAID_ERROR_HANDLING
	#if !defined(ALLOCATE_SENSE_BUFFER) || (ALLOCATE_SENSE_BUFFER==0)
		#error "Must allocate sense buffer!"
	#endif
	#define ERROR_HANDLING_SUPPORT	1	/* DDF related code is still using old implemention */
	#ifdef NEW_MEM_ALLOC
		#error "RAID_ERROR_HANDLING doesn't support NEW_MEM_ALLOC yet."
	#endif
	#define SUPPORT_DO_TEST			1	/* dbg APIs */
	#define MEDIA_DEFECT_FIXING		1	/* Fix the media defect found */
#else
	#define ERROR_HANDLING_SUPPORT	0	/* DDF related code is still using old implemention */

#endif

/* Cache */
#ifndef _OS_LINUX /*linux define it within config file*/
#ifndef HAVE_PRD_SKIP
#   define CACHE_MODULE_SUPPORT
#endif
#ifdef CACHE_MODULE_SUPPORT
#   define NEW_CACHE_SUPPORT
#endif
#endif
//#	define CACHE_FREE_DISK_ENABLE          1
#	ifndef USE_NEW_SGTABLE
#		define SUPPORT_VIRTUAL_AND_PHYSICAL_SG
#	endif

#if defined(SUPPORT_RAID6)
#define MULTIPLE_BGA_RATE					1
#endif /*SUPPORT_RAID6*/

#ifdef SUPPORT_DISK_GRP
	#define MAX_LD_SUPPORTED_PERFORMANCE          64
    #ifdef BLK_NUMBER_CHANGE
	#define MAX_BLOCK_SUPPORTED_PERFORMANCE       1024
    #else
	#define MAX_BLOCK_SUPPORTED_PERFORMANCE       240
    #endif
#else
	#define MAX_LD_SUPPORTED_PERFORMANCE          8
	#define MAX_BLOCK_SUPPORTED_PERFORMANCE       128
#endif

#ifdef CACHE_MODULE_SUPPORT
	#include "mv_cache.h"
#endif

#endif /* __MV_RAID_H__ */

