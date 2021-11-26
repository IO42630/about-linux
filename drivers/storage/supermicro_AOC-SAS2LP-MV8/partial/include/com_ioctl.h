#ifndef __MV_COM_IOCTL_H__
#define __MV_COM_IOCTL_H__

#if defined(_OS_WINDOWS) && !defined(_OS_FIRMWARE)
#include <ntddscsi.h>
#elif defined(_OS_LINUX)

#endif /* _OS_WINDOWS */

/* private IOCTL commands */
#define MV_IOCTL_CHECK_DRIVER                                \
	    CTL_CODE(FILE_DEVICE_CONTROLLER,                 \
                     0x900, METHOD_BUFFERED,                 \
                     FILE_READ_ACCESS | FILE_WRITE_ACCESS)	

/*
 * MV_IOCTL_LEAVING_S0 is a notification when the system is going 
 * to leaving S0. This gives the driver a chance to do some house
 * keeping work before system really going to sleep.
 *
 * The MV_IOCTL_LEAVING_S0 will be translated to APICDB0_ADAPTER/
 * APICDB1_ADAPTER_POWER_STATE_CHANGE and passed down along the
 * module stack. A module shall handle this request if necessary.
 *
 * Upon this request, usually the Cache module shall flush all
 * cached data. And the RAID module shall auto-pause all background
 * activities.
 */
#define MV_IOCTL_LEAVING_S0                                \
	    CTL_CODE(FILE_DEVICE_CONTROLLER,                 \
                     0x901, METHOD_BUFFERED,                 \
                     FILE_READ_ACCESS | FILE_WRITE_ACCESS)	

/*
 * MV_IOCTL_REENTER_S0 is a notification when the system is going 
 * to re-entering S0. This gives the driver a chance to resume
 * something when system wakes up.
 *
 * The MV_IOCTL_REENTER_S0 will be translated to APICDB0_ADAPTER/
 * APICDB1_ADAPTER_POWER_STATE_CHANGE (CDB2 is 1) and passed down 
 * along the module stack. 
 * A module shall handle this request if necessary.
 */
#define MV_IOCTL_REENTER_S0                                \
	    CTL_CODE(FILE_DEVICE_CONTROLLER,                 \
                     0x902, METHOD_BUFFERED,                 \
                     FILE_READ_ACCESS | FILE_WRITE_ACCESS)	

/* Used for notifying shutdown from dispatch */
#define MV_IOCTL_SHUTDOWN                               \
	    CTL_CODE(FILE_DEVICE_CONTROLLER,                 \
                     0x903, METHOD_BUFFERED,                 \
                     FILE_READ_ACCESS | FILE_WRITE_ACCESS)	
// private ioctrl for scsi trim
#define MV_IOCTL_TRIM_SCSI                               \
	    CTL_CODE(FILE_DEVICE_CONTROLLER,                 \
                     0x905, METHOD_BUFFERED,                 \
                     FILE_WRITE_ACCESS)	

/* IOCTL signature */
#define MV_IOCTL_DRIVER_SIGNATURE                "mv61xxsg"
#define MV_IOCTL_DRIVER_SIGNATURE_LENGTH         8

/* IOCTL command status */
#define IOCTL_STATUS_SUCCESS                     0
#define IOCTL_STATUS_INVALID_REQUEST             1
#define IOCTL_STATUS_ERROR                       2


/*IOCTL code on linux*/
#ifdef _OS_LINUX
#define API_BLOCK_IOCTL_DEFAULT_FUN	0x1981
#define API_IOCTL_DEFAULT_FUN			0x00
#define	API_IOCTL_GET_VIRTURL_ID		(API_IOCTL_DEFAULT_FUN + 1)
#define	API_IOCTL_GET_HBA_COUNT		(API_IOCTL_DEFAULT_FUN + 2)
#define	API_IOCTL_LOOKUP_DEV			(API_IOCTL_DEFAULT_FUN + 3)
#define  API_IOCTL_CHECK_VIRT_DEV           (API_IOCTL_DEFAULT_FUN + 4)
#define  API_IOCTL_GET_ENC_ID               	(API_IOCTL_DEFAULT_FUN + 5)
#define  API_IOCTL_MAX                      		(API_IOCTL_DEFAULT_FUN + 6)
#endif


#if defined(SUPPORT_ESATA) || defined(SUPPORT_DRIVER_FEATURE)
#define MV_IOCTL_CHECK_DEVICE                                \
	    CTL_CODE(FILE_DEVICE_CONTROLLER,                 \
                     0x904, METHOD_BUFFERED,                 \
                     FILE_READ_ACCESS | FILE_WRITE_ACCESS)	
#endif

#ifndef _OS_BIOS
#pragma pack(8)
#endif  /* _OS_BIOS */

typedef struct _MV_IOCTL_BUFFER
{
#if defined(_OS_WINDOWS) && !defined(_OS_FIRMWARE)
	SRB_IO_CONTROL Srb_Ctrl;
#endif /* _OS_WINDOWS */
	MV_U8          Data_Buffer[32];
} MV_IOCTL_BUFFER, *PMV_IOCTL_BUFFER;

#ifndef _OS_BIOS
#pragma pack()
#endif /* _OS_BIOS */

#endif /* __MV_COM_IOCTL_H__ */
