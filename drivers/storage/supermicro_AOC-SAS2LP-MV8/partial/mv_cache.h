#ifndef _CACHE_PARAMETER_FILE_
#define _CACHE_PARAMETER_FILE_
/*
*
 *  these is used for count related and the number is sector
 */

#define SECTOR_SHIFT     9

////////////////////////////////////////////////
#define MAX_PAGES_PER_CU ( 32*4 )
#define COUNT_PAGE    (512 * 4  )
#define SHIFT_CNSECTOR_PER_PAGE (3)  //This valu is equal to log2 (COUNT_SECTOR_PER_PAGE)



#define MIN_CACHE_UNIT	 ( ( 1 << ( K_SHIFT - SECTOR_SHIFT ) )   * 128)   //sector  128k
#define SHIFT_FACTOR_WIDTH 31

//////////////////////////////////////////////////////////////////////////////

#define COUNT_CU      ((COUNT_PAGE) >> 4 )
#define COUNT_CACHE_REQUEST  (COUNT_CU << 2)
#define COUNT_VALIDRANGE (COUNT_CU * 3)


#define MAX_CDEVICE_SUPPORT MAX_LD_SUPPORTED_PERFORMANCE
#define MAX_CTARGET_NUM MV_MAX_TARGET_NUMBER 


#define COUNT_SECTOR_LARGE_REQUEST  (512*2)  //in sectors, so the value no is 512k


/* dertermine the low and high mark
*/
#define CACHE_LOW_MARK_PAGE  ( COUNT_PAGE >> 2)  
#define CACHE_HIGH_MARK_PAGE (  (COUNT_PAGE >> 2) * 3 )

#define CACHE_LOW_MARK_CU  ( COUNT_CU >> 3 )
#define CACHE_HIGH_MARK_CU  (COUNT_CU >> 1)

#define CACHE_LOW_MARK_VR  ((COUNT_VALIDRANGE) >> 3)
#define CACHE_HIGH_MARK_VR   (  COUNT_VALIDRANGE >> 1)

/*this define are used for seq recognize*/
#define WATERMARK_SERIAL_SEQ 1 
#define WATERMARK_SERIAL_LOC 8

#define MARK_SMALL_BLOCK 16 //8K


/*MAX AND MIN PREREAD LENGTH  */
#define MAX_PREREAD_LENGTH	1024
#define MIN_PREREAD_LENGTH	128


/*these define are used for release resource config*/

#define RELEASE_LOOP 0xff
#define RELEASE_COUNT_PER_DEVICE 0xfff


#define COUNT_MAXLOGSEQ_PER_DEVICE		20
#define COUNT_MAXLOGLOC_PER_DEVICE		10
#define MAX_MISS_COUNT		20
#define MAX_HIT_COUNT_ADJUST  30

/*
 * these macros are for time interval adjust
 */
#define TIME_INTERVAL_IDLE 2
#define TIME_INTERVAL_BUSY 2





#if 0
#define CACHE_DBG_INFO(_x_)	do {if (g_cache_print & PRINT_D0) {MV_PRINT("Cache Engine: ");	MV_PRINT _x_; } } while (0)
#else
#define CACHE_DBG_INFO(_x_)	
#if defined(SUPPORT_CHANGE_DEBUG_MODE)
extern MV_U16 mv_debug_mode;
#define CACHE_DBGn_INFO(_x_,n)	do {if ((CACHE_DEBUG_INFO & mv_debug_mode) && (g_cache_print & MV_BIT(n))) {MV_PRINT("Cache Engine d"#n":" );	MV_PRINT _x_; } } while (0)

#else

//#define CACHE_DBG_PRINT
#ifdef CACHE_DBG_PRINT
#define CACHE_DBGn_INFO(_x_,n)	do {if (g_cache_print & MV_BIT(n)) {MV_PRINT("Cache Engine d"#n":" );	MV_PRINT _x_; } } while (0)
#else
#define CACHE_DBGn_INFO(_x_,n)
#endif

#endif /*SUPPORT_CHANGE_DEBUG_MODE*/

#endif
#if 0 
#define C_PRINT MV_PRINT("\n%s %s %d",__FILE__,__FUNCTION__,__LINE__);MV_PRINT
#else
#define C_PRINT MV_PRINT
#endif

/*dertermine system busy?*/
#define WATER_MARK_BUSY 10


/*
  debug options
*/
#ifndef DBG
#define CACHE_DEBUG_RES 	0
#define CACHE_DEBUG_PAGE 	0
#define CACHE_CRC_CHECK		0 /* this should always be 0*/
#define CACHE_DEBUG_BBU         0
#undef	CACHE_DEBUG_SEQ
#else 
#define CACHE_DEBUG_RES 	1
#define CACHE_DEBUG_PAGE 	1
#define CACHE_CRC_CHECK		0  /* this should always be 0*/
#define CACHE_DEBUG_BBU         1
#undef	CACHE_DEBUG_SEQ
#endif

/*template configures
*/
//#define  CACHE_BBU_ECC

//feature control
#define CACHE_DEVICE_LOCK 	0
#define CACHE_SUPPORT_LOC	0
#define CACHE_EXTENT_WIDTH_R10  0
#define CACHE_SUPPORT_SYNC_CMD  1
#define CACHE_WT_FEATURE	0
#define CACHE_OP_LOG		0

#if defined(_OS_LINUX)
#define _XOR_DMA
#endif
#endif



