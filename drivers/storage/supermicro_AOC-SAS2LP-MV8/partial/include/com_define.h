#ifndef COM_DEFINE_H
#define COM_DEFINE_H

#include "mv_os.h"

/*
 *  This file defines Marvell OS independent primary data type for all OS.
 *
 *  We have macros to differentiate different CPU and OS.
 *
 *  CPU definitions:
 *  _CPU_X86_16B  
 *  Specify 16bit x86 platform, this is used for BIOS and DOS utility.
 *  _CPU_X86_32B
 *  Specify 32bit x86 platform, this is used for most OS drivers.
 *  _CPU_IA_64B
 *  Specify 64bit IA64 platform, this is used for IA64 OS drivers.
 *  _CPU_AMD_64B
 *  Specify 64bit AMD64 platform, this is used for AMD64 OS drivers.
 *
 *  OS definitions:
 *  _OS_WINDOWS
 *  _OS_LINUX
 *  _OS_FREEBSD
 *  _OS_BIOS
 *  __QNXNTO__
 */

#if defined(_OS_DOS) && defined(COM_DEBUG)
 #include "vsprintf.h"
#endif

#if !defined(IN)
#   define IN
#endif

#if !defined(OUT)
#   define OUT
#endif

#if defined(_OS_LINUX) || defined(__QNXNTO__) || defined(_OS_UKRN)
#   define    BUFFER_PACKED               __attribute__((packed))
#elif defined(_OS_WINDOWS) || defined(_OS_DOS)
    #if !defined(_OS_FIRMWARE)
#   define    BUFFER_PACKED
    #else
#   define    BUFFER_PACKED               __attribute__((packed))
    #endif
#elif defined(_OS_BIOS)
#   define    BUFFER_PACKED
#endif /* defined(_OS_LINUX) || defined(__QNXNTO__) */

#define MV_BIT(x)                         (1UL << (x))

#if !defined(NULL)
#   define NULL 0
#endif  /* NULL */

#define MV_TRUE                           1
#define MV_FALSE                          0
#define MV_SUCCESS						  1
#define MV_FAIL							  0
#define MV_REG_FAIL 1
#define MV_REG_SUCCESS 0



typedef unsigned char  MV_BOOLEAN, *MV_PBOOLEAN;
typedef unsigned char  MV_U8, *MV_PU8;
typedef signed char  MV_I8, *MV_PI8;

typedef unsigned short  MV_U16, *MV_PU16;
typedef signed short  MV_I16, *MV_PI16;

typedef void    MV_VOID, *MV_PVOID;
typedef unsigned long MV_ULONG, *MV_PULONG;

#ifdef _OS_BIOS
    typedef MV_U8 GEN_FAR*  MV_LPU8;
    typedef MV_I8 GEN_FAR*  MV_LPI8;
    typedef MV_U16 GEN_FAR* MV_LPU16;
    typedef MV_I16 GEN_FAR* MV_LPI16;

    typedef MV_U32 GEN_FAR* MV_LPU32;
    typedef MV_I32 GEN_FAR* MV_LPI32;
    typedef void GEN_FAR*   MV_LPVOID;
#else
    typedef void            *MV_LPVOID;
#endif /* _OS_BIOS */

/* Pre-define segment in C code*/
#if defined(_OS_BIOS)
#   define BASEATTR         __based(__segname("_CODE")) 
#   define BASEATTRData     __based(__segname("_CODE")) 
#else
#   define BASEATTR 
#endif /* _OS_BIOS */

#ifdef DEBUG_COM_SPECIAL
	#define MV_DUMP_COM_SPECIAL(pString)  						{bDbgPrintStr(pString);bCOMEnter();}
	#define MV_DUMP32_COM_SPECIAL(pString, value) 				bDbgPrintStr_U32(pString, value)
	#define MV_DUMP16_COM_SPECIAL(pString, value)  				bDbgPrintStr_U16(pString, value)
	#define MV_DUMP32_COM_SPECIAL3(pString, value1, value2)  	bDbgPrintStr_U32_3(pString, value1, value2)
	#define MV_DUMP8_COM_SPECIAL(pString, value)  				bDbgPrintStr_U8(pString, value)	
	#define MV_HALTKEY_SPECIAL									waitForKeystroke()

#else
	#define MV_DUMP_COM_SPECIAL(pString)  						
	#define MV_DUMP32_COM_SPECIAL(pString, value) 				
	#define MV_DUMP16_COM_SPECIAL(pString, value)  				
	#define MV_DUMP32_COM_SPECIAL3(pString, value1, value2)  	
	#define MV_DUMP8_COM_SPECIAL(pString, value)  				
	#define MV_HALTKEY_SPECIAL									
#endif
/* For debug version only */
#if (defined(DEBUG_BIOS)) || (defined(_OS_DOS) && defined(COM_DEBUG))
 #ifdef DEBUG_SHOW_ALL
	#define MV_DUMP32(_x_) 		{mvDebugDumpU32(_x_);bCOMEnter();}
	#define MV_DUMP16(_x_)  	{mvDebugDumpU16(_x_);bCOMEnter();}
	#define MV_DUMP8(_x_)  		{mvDebugDumpU8(_x_);bCOMEnter();}
	#define MV_DUMPC32(_x_)  	{mvDebugDumpU32(_x_);bCOMEnter();}
	#define MV_DUMPC16(_x_)  	{mvDebugDumpU16(_x_);bCOMEnter();}
	#define MV_DUMPC8(_x_)  	{mvDebugDumpU8(_x_);bCOMEnter();}
	#define MV_DUMPE32(_x_) 	{mvDebugDumpU32(_x_);bCOMEnter();}
	#define MV_DUMPE16(_x_) 	{mvDebugDumpU16(_x_);bCOMEnter();}
	#define MV_DUMPE8(_x_)  	{mvDebugDumpU8(_x_);bCOMEnter();}
 	#define MV_DUMP_COM(pString)  						{bDbgPrintStr(pString);bCOMEnter();}
	#define MV_DUMP32_COM(pString, value) 				bDbgPrintStr_U32(pString, value)
	#define MV_DUMP16_COM(pString, value)  				bDbgPrintStr_U16(pString, value)
	#define MV_DUMP32_COM3(pString, value1, value2)  	bDbgPrintStr_U32_3(pString, value1, value2)
	#define MV_DUMP8_COM(pString, value)  				bDbgPrintStr_U8(pString, value)
 #else
	#define MV_DUMP32(_x_) 		//{mvDebugDumpU32(_x_);bCOMEnter();}
	#define MV_DUMP16(_x_)  	//{mvDebugDumpU16(_x_);bCOMEnter();}
	#define MV_DUMP8(_x_)  		//{mvDebugDumpU8(_x_);bCOMEnter();}
	#define MV_DUMPC32(_x_)  	//{mvDebugDumpU32(_x_);bCOMEnter();}
	#define MV_DUMPC16(_x_)  	//{mvDebugDumpU16(_x_);bCOMEnter();}
	#define MV_DUMPC8(_x_)  	//{mvDebugDumpU8(_x_);bCOMEnter();}
	#define MV_DUMPE32(_x_) 	//{mvDebugDumpU32(_x_);bCOMEnter();}
	#define MV_DUMPE16(_x_) 	//{mvDebugDumpU16(_x_);bCOMEnter();}
	#define MV_DUMPE8(_x_)  	//{mvDebugDumpU8(_x_);bCOMEnter();}
 	#define MV_DUMP_COM(pString)  						//{bDbgPrintStr(pString);bCOMEnter();}
	#define MV_DUMP32_COM(pString, value) 				//bDbgPrintStr_U32(pString, value)
	#define MV_DUMP16_COM(pString, value)  				//bDbgPrintStr_U16(pString, value)
	#define MV_DUMP32_COM3(pString, value1, value2)  	//bDbgPrintStr_U32_3(pString, value1, value2)
	#define MV_DUMP8_COM(pString, value)  				//bDbgPrintStr_U8(pString, value)
 
 #endif
 
	#define MV_BIOSDEBUG(pString, value)				bDbgPrintStr_U32(pString, value)				
	#define MV_HALTKEY			waitForKeystroke()
	#define MV_ENTERLINE		//mvChangLine()
#else
	#define MV_DUMP32(_x_) 		//{mvDebugDumpU32(_x_);bCOMEnter();}
	#define MV_DUMP16(_x_)  	//{mvDebugDumpU16(_x_);bCOMEnter();}
	#define MV_DUMP8(_x_)  		//{mvDebugDumpU8(_x_);bCOMEnter();}
	#define MV_DUMPC32(_x_)  	//{mvDebugDumpU32(_x_);bCOMEnter();}
	#define MV_DUMPC16(_x_)  	//{mvDebugDumpU16(_x_);bCOMEnter();}
	#define MV_DUMPC8(_x_)  	//{mvDebugDumpU8(_x_);bCOMEnter();}
	#define MV_DUMPE32(_x_) 	//{mvDebugDumpU32(_x_);bCOMEnter();}
	#define MV_DUMPE16(_x_) 	//{mvDebugDumpU16(_x_);bCOMEnter();}
	#define MV_DUMPE8(_x_)  	//{mvDebugDumpU8(_x_);bCOMEnter();}
 	#define MV_DUMP_COM(pString)  						//{bDbgPrintStr(pString);bCOMEnter();}
	#define MV_DUMP32_COM(pString, value) 				//bDbgPrintStr_U32(pString, value)
	#define MV_DUMP16_COM(pString, value)  				//bDbgPrintStr_U16(pString, value)
	#define MV_DUMP32_COM3(pString, value1, value2)  	//bDbgPrintStr_U32_3(pString, value1, value2)
	#define MV_DUMP8_COM(pString, value)  				//bDbgPrintStr_U8(pString, value)

	#define MV_BIOSDEBUG(pString, value)
#if defined(_OS_DOS) && defined(MV_DEBUG)
	#define MV_HALTKEY mv_waitfor_key_stroke()
#else
#if defined(DEBUG_FW30)
	#define MV_HALTKEY  waitForKeystroke()
#else
	#define MV_HALTKEY
#endif
#endif	
	#define MV_ENTERLINE
	
#endif

#if defined(_OS_LINUX) || defined(__QNXNTO__) || defined(_OS_FIRMWARE) || defined(_OS_MAC)
    /* unsigned/signed long is 64bit for AMD64, so use unsigned int instead */
    typedef unsigned int MV_U32, *MV_PU32;
    typedef   signed int MV_I32, *MV_PI32;
    typedef   signed long MV_ILONG, *MV_PILONG;
#else
    /* unsigned/signed long is 32bit for x86, IA64 and AMD64 */
    typedef unsigned long MV_U32, *MV_PU32;
    typedef   signed long MV_I32, *MV_PI32;
#endif /*  defined(_OS_LINUX) || defined(__QNXNTO__) */

#if defined(_OS_WINDOWS) || defined(_OS_DOS) || defined(_OS_FIRMWARE)
  #if !defined(_OS_FIRMWARE)
    typedef unsigned __int64 _MV_U64;
    typedef   signed __int64 _MV_I64;
  #else
    typedef unsigned long long _MV_U64;
    typedef   signed long long _MV_I64;
  #endif  
#elif defined(_OS_LINUX) || defined(__QNXNTO__)
    typedef unsigned long long _MV_U64;
    typedef   signed long long _MV_I64;
#elif defined(_OS_FREEBSD)
#   error "No Where"
#elif defined(_OS_BIOS)
//
//NA
//
#elif defined(_OS_MAC)
/*typedef unsigned char  MV_BOOLEAN, *MV_PBOOLEAN;
typedef unsigned char  MV_U8, *MV_PU8;
typedef signed char  MV_I8, *MV_PI8;

typedef unsigned short  MV_U16, *MV_PU16;
typedef signed short  MV_I16, *MV_PI16;

typedef void    MV_VOID, *MV_PVOID;
typedef unsigned int MV_U32, *MV_PU32;
typedef   signed int MV_I32, *MV_PI32;*/
typedef unsigned long long _MV_U64;
typedef   signed long long _MV_I64;
#else
#   error "No Where"
#endif /* _OS_WINDOWS */

//typedef _MV_U64 BUS_ADDRESS;

#ifdef _OS_LINUX
#   if defined(__KCONF_64BIT__)
#      define _SUPPORT_64_BIT
#   else
#      ifdef _SUPPORT_64_BIT
#         error Error 64_BIT CPU Macro
#      endif
#   endif /* defined(__KCONF_64BIT__) */
#elif defined(_OS_BIOS) || defined(__QNXNTO__)
#   undef  _SUPPORT_64_BIT
#else
  #if !defined(_OS_FIRMWARE)
#   define _SUPPORT_64_BIT
  #else
#   if defined(__KCONF_64BIT__)
#      define _SUPPORT_64_BIT
#   else
#      ifdef _SUPPORT_64_BIT
#         error Error 64_BIT CPU Macro
#      endif
#   endif /* defined(__KCONF_64BIT__) */
  #endif /* _OS_FIRMWARE */
#endif /* _OS_LINUX */

/*
 * Primary Data Type
 */
#if defined(_OS_WINDOWS) || defined(_OS_DOS) || defined(_OS_FIRMWARE) || defined(_OS_MAC)
  #if !defined(_OS_FIRMWARE)
    typedef union {
        struct {
            MV_U32 low;
            MV_U32 high;
        } parts;
        _MV_U64 value;
    } MV_U64, *PMV_U64, *MV_PU64;
  #else
    typedef union {
        struct {
#   if defined (__MV_LITTLE_ENDIAN__)
            MV_U32 low;
            MV_U32 high;
#   elif defined (__MV_BIG_ENDIAN__)
            MV_U32 high;
            MV_U32 low;
#   else
#           error "undefined endianness"
#   endif /* __MV_LITTLE_ENDIAN__ */
        } parts;
        _MV_U64 value;
    } MV_U64, *PMV_U64, *MV_PU64;
  #endif	
#elif defined(_OS_LINUX) || defined(__QNXNTO__)
    typedef union {
        struct {
#   if defined (__MV_LITTLE_ENDIAN__)
            MV_U32 low;
            MV_U32 high;
#   elif defined (__MV_BIG_ENDIAN__)
            MV_U32 high;
            MV_U32 low;
#   else
#           error "undefined endianness"
#   endif /* __MV_LITTLE_ENDIAN__ */
        } parts;
        _MV_U64 value;
    } MV_U64, *PMV_U64, *MV_PU64;
#else
/* BIOS compiler doesn't support 64 bit data structure. */
    typedef union {
        struct {
             MV_U32 low;
             MV_U32 high;
        };
				struct {
					MV_U32 low;
					MV_U32 high;
				}parts;
        struct {
             MV_U32 value;
             MV_U32 value1;
        };
    } _MV_U64,MV_U64, *MV_PU64, *PMV_U64;
#endif /* defined(_OS_LINUX) || defined(_OS_WINDOWS) || defined(__QNXNTO__)*/

typedef _MV_U64 BUS_ADDRESS;

/* PTR_INTEGER is necessary to convert between pointer and integer. */
#if defined(_SUPPORT_64_BIT)
   typedef _MV_U64 MV_PTR_INTEGER;
#else
   typedef MV_U32 MV_PTR_INTEGER;
#endif /* defined(_SUPPORT_64_BIT) */

#ifdef _SUPPORT_64_BIT
#define _64_BIT_COMPILER     1
#endif

/* LBA is the logical block access */
typedef MV_U64 MV_LBA;

#if defined(_CPU_16B)
    typedef MV_U32 MV_PHYSICAL_ADDR;
#else
    typedef MV_U64 MV_PHYSICAL_ADDR;
#endif /* defined(_CPU_16B) */

#if defined (_OS_WINDOWS)
	#if !defined(_OS_FIRMWARE)
		typedef MV_PVOID MV_FILE_HANDLE;
	#else
		typedef MV_I32 MV_FILE_HANDLE;
	#endif
#elif defined(_OS_LINUX) || defined(__QNXNTO__) || defined (_OS_MAC)
typedef MV_I32 MV_FILE_HANDLE;
#elif defined (_OS_DOS)
typedef int MV_FILE_HANDLE;
#endif

#include "com_product.h"

/* OS_LINUX depedent definition*/

#if defined(_OS_LINUX) || defined(__QNXNTO__)
#define hba_local_irq_disable() ossw_local_irq_disable()
#define hba_local_irq_enable() ossw_local_irq_enable()
#define hba_local_irq_save(flag) ossw_local_irq_save(&flag)
#define hba_local_irq_restore(flag) ossw_local_irq_restore(&flag)

/* expect pointers */
#define OSSW_LOCAL_IRQ_SAVE(flag)	ossw_local_irq_save(&flag)
#define OSSW_LOCAL_IRQ_RESTORE(flag)	ossw_local_irq_restore(&flag)
#define OSSW_INIT_SPIN_LOCK(ext) ossw_init_spin_lock(ext)
#define OSSW_SPIN_LOCK(ext)            ossw_spin_lock(ext)
#define OSSW_SPIN_UNLOCK(ext)          ossw_spin_unlock(ext)
#define OSSW_SPIN_LOCK_IRQ(ext)            ossw_spin_lock_irq(ext)
#define OSSW_SPIN_UNLOCK_IRQ(ext)          ossw_spin_unlock_irq(ext)
#define OSSW_SPIN_LOCK_IRQSAVE(ext, flag)          ossw_spin_lock_irq_save(ext, &flag)
#define OSSW_SPIN_UNLOCK_IRQRESTORE(ext, flag)           ossw_spin_unlock_irq_restore(ext, &flag)

/* for hw multi-queue */
#define OSSW_GET_CPU_NUM() ossw_get_cpu_num()

#define OSSW_SPIN_LOCK_HBA(ext, flag) ossw_spin_lock_hba(ext, &flag)
#define OSSW_SPIN_UNLOCK_HBA(ext, flag) ossw_spin_unlock_hba(ext, &flag)
#define OSSW_SPIN_LOCK_RESOURCE(ext, flag) ossw_spin_lock_resource(ext, &flag)
#define OSSW_SPIN_UNLOCK_RESOURCE(ext, flag) ossw_spin_unlock_resource(ext, &flag)
#define OSSW_SPIN_LOCK_WAIT_QUEUE(ext, flag) ossw_spin_lock_wait_queue(ext, &flag)
#define OSSW_SPIN_UNLOCK_WAIT_QUEUE(ext, flag) ossw_spin_unlock_wait_queue(ext, &flag)
#define OSSW_SPIN_LOCK_COMPL_QUEUE(ext, flag) ossw_spin_lock_compl_queue(ext, &flag)
#define OSSW_SPIN_UNLOCK_COMPL_QUEUE(ext, flag) ossw_spin_unlock_compl_queue(ext, &flag)
#define OSSW_SPIN_LOCK_CORE_QUEUE(ext, flag) ossw_spin_lock_core_queue(ext, &flag)
#define OSSW_SPIN_UNLOCK_CORE_QUEUE(ext, flag) ossw_spin_unlock_core_queue(ext, &flag)
#define OSSW_SPIN_LOCK_ROOT(ext, flag, root_id) ossw_spin_lock_root(ext, &flag, root_id)
#define OSSW_SPIN_UNLOCK_ROOT(ext, flag, root_id) ossw_spin_unlock_root(ext, &flag, root_id)
#define OSSW_SPIN_LOCK_HW_QUEUE(ext, flag, queue_id) ossw_spin_lock_hw_queue(ext, &flag, queue_id)
#define OSSW_SPIN_UNLOCK_HW_QUEUE(ext, flag, queue_id) ossw_spin_unlock_hw_queue(ext, &flag, queue_id)
#define OSSW_SPIN_LOCK_CORE(ext, flag) ossw_spin_lock_core(ext, &flag)
//#define OSSW_SPIN_TRYLOCK_CORE(ext, flag) ossw_spin_trylock_core(ext, &flag)
#define OSSW_SPIN_UNLOCK_CORE(ext, flag) ossw_spin_unlock_core(ext, &flag)
#define OSSW_SPIN_LOCK_HW_WQ(ext, flag, queue_id) ossw_spin_lock_hw_wq(ext, &flag, queue_id)
#define OSSW_SPIN_UNLOCK_HW_WQ(ext, flag, queue_id) ossw_spin_unlock_hw_wq(ext, &flag, queue_id)
#define OSSW_SPIN_LOCK_HW_CQ(ext, flag, queue_id) ossw_spin_lock_hw_cq(ext, &flag, queue_id)
#define OSSW_SPIN_UNLOCK_HW_CQ(ext, flag, queue_id) ossw_spin_unlock_hw_cq(ext, &flag, queue_id)

#ifdef SUPPORT_STAGGERED_SPIN_UP
#define OSSW_SPIN_LOCK_IRQSAVE_SPIN_UP(ext, flag)          ossw_spin_lock_irq_save_spin_up(ext, &flag)
#define OSSW_SPIN_UNLOCK_IRQRESTORE_SPIN_UP(ext, flag)           ossw_spin_unlock_irq_restore_spin_up(ext, &flag)
#endif
/* Delayed Execution Services */
#define OSSW_INIT_TIMER(ptimer) ossw_init_timer(ptimer)

#else /* For Windows */

#define hba_local_irq_disable()
#define hba_local_irq_enable()
#define hba_local_irq_save(flag) 
#define hba_local_irq_restore(flag) 

/* expect pointers */
#define OSSW_LOCAL_IRQ_SAVE(flag)
#define OSSW_LOCAL_IRQ_RESTORE(flag)
#define OSSW_INIT_SPIN_LOCK(plock) 
#define OSSW_SPIN_LOCK(plock)           
#define OSSW_SPIN_UNLOCK(plock)           
#define OSSW_SPIN_LOCK_IRQ(plock)
#define OSSW_SPIN_UNLOCK_IRQ(plock)
#define OSSW_SPIN_LOCK_IRQSAVE(plock, flag)          
#define OSSW_SPIN_UNLOCK_IRQRESTORE(plock, flag)
#define OSSW_GET_CPU_NUM() (16)
#define OSSW_SPIN_LOCK_HBA(ext, flag)
#define OSSW_SPIN_UNLOCK_HBA(ext, flag)
#define OSSW_SPIN_LOCK_RESOURCE(ext, flag)
#define OSSW_SPIN_UNLOCK_RESOURCE(ext, flag)
#define OSSW_SPIN_LOCK_WAIT_QUEUE(ext, flag)
#define OSSW_SPIN_UNLOCK_WAIT_QUEUE(ext, flag)
#define OSSW_SPIN_LOCK_COMPL_QUEUE(ext, flag)
#define OSSW_SPIN_UNLOCK_COMPL_QUEUE(ext, flag)
#define OSSW_SPIN_LOCK_CORE_QUEUE(ext, flag)
#define OSSW_SPIN_UNLOCK_CORE_QUEUE(ext, flag)
#define OSSW_SPIN_LOCK_ROOT(ext, flag, root_id) 
#define OSSW_SPIN_UNLOCK_ROOT(ext, flag, root_id)
#define OSSW_SPIN_LOCK_HW_QUEUE(ext, flag, queue_id)
#define OSSW_SPIN_UNLOCK_HW_QUEUE(ext, flag, queue_id)
#define OSSW_SPIN_LOCK_CORE(ext, flag) 
//#define OSSW_SPIN_TRYLOCK_CORE(ext, flag) 
#define OSSW_SPIN_UNLOCK_CORE(ext, flag)
#define OSSW_SPIN_LOCK_HW_WQ(ext, flag, queue_id)
#define OSSW_SPIN_UNLOCK_HW_WQ(ext, flag, queue_id)
#define OSSW_SPIN_LOCK_HW_CQ(ext, flag, queue_id)
#define OSSW_SPIN_UNLOCK_HW_CQ(ext, flag, queue_id)
#ifdef SUPPORT_STAGGERED_SPIN_UP
#define OSSW_SPIN_LOCK_IRQSAVE_SPIN_UP(plock, flag)
#define OSSW_SPIN_UNLOCK_IRQRESTORE_SPIN_UP(plock, flag)
#endif

/* Delayed Execution Services */
#define OSSW_INIT_TIMER(ptimer) 

#endif


#if !defined( likely )
#if defined( SUPPORT_ROC )&&defined( _OS_FIRMWARE )
#define likely(x)		__builtin_expect((x),1)
#define unlikely(x)		__builtin_expect((x),0)
#else
#define likely(x)		(x)
#define unlikely(x)		(x)
#endif
#endif

#if defined( SUPPORT_ROC )&&defined( _OS_FIRMWARE )
#define MV_GO_SECT(class, grp)		__attribute__((section(".cold_rain_"#grp)))
#else
#define MV_GO_SECT(class, grp)
#endif

#if defined(_OS_LINUX)

#if defined(SUPPORT_CHANGE_DEBUG_MODE)
#define GENERAL_DEBUG_INFO	MV_BIT(0)	/*For MV_DPRINT*/
#define CORE_DEBUG_INFO		MV_BIT(1)	/*Core debug info: CORE_PRINT, CORE_EH_PRINT*/
#define RAID_DEBUG_INFO		MV_BIT(2)	/*Raid debug info*/
#define CACHE_DEBUG_INFO	MV_BIT(3)	/*Cache debug info*/
#define LL_DEBUG_INFO	MV_BIT(4)	/*LowLevel debug info*/
#define CORE_FULL_DEBUG_INFO	(CORE_DEBUG_INFO | \
							GENERAL_DEBUG_INFO) /*CORE_DPRINT, CORE_EH_PRINT, CORE_EVENT_PRINT*/
#define RAID_FULL_DEBUG_INFO	(RAID_DEBUG_INFO | \
							GENERAL_DEBUG_INFO) 
#define CACHE_FULL_DEBUG_INFO	(CACHE_DEBUG_INFO | \
							GENERAL_DEBUG_INFO) 
#endif /*SUPPORT_CHANGE_DEBUG_MODE*/

#define sg_map(x)	hba_map_sg_to_buffer(x)
#define sg_unmap(x)	hba_unmap_sg_to_buffer(x)

#define time_is_expired(x) 	ossw_time_expired(x)
#define EVENT_SET_DELAY_TIME(x, y) ((x) = ossw_set_expired_time(y))

#define msi_enabled(x)	hba_msi_enabled(x)
#ifdef SUPPORT_MSIX_INT
#define msix_enabled(x)	hba_msix_enabled(x)
#else
#define msix_enabled(x)   MV_FALSE
#endif
#define test_enabled(x) hba_test_enabled(x)
#else
#define sg_map(x)
#define sg_unmap(x)

#define time_is_expired(x)	MV_TRUE	
#define EVENT_SET_DELAY_TIME(x, y)
#ifdef SUPPORT_MSI
#define msi_enabled(x)	hba_msi_enabled(x)
#else
#define msi_enabled(x)	MV_FALSE
#endif
#ifdef SUPPORT_MSIX_INT
#define msix_enabled(x)	hba_msix_enabled(x)
#else
#define msix_enabled(x) MV_FALSE
#endif
#ifdef SUPPORT_INEJECT_ERROR
#define test_enabled(x) MV_TRUE
#else
#define test_enabled(x) MV_FALSE
#endif
#ifndef MV_API_EXPORTS

#if defined(_OS_BIOS)||defined(SUPPORT_ROC)
static inline MV_BOOLEAN __is_scsi_cmd_simulated(MV_U8 cmd_type){return MV_FALSE;};
#endif

#endif

#endif

#endif /* COM_DEFINE_H */
