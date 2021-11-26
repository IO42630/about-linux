#ifndef  __MV_COM_EXTERN_H__
#define  __MV_COM_EXTERN_H__

#include "com_define.h"
/* Target device type */
#define TARGET_TYPE_LD                          	0
#define TARGET_TYPE_FREE_PD                 	1

#define DISK_TYPE_RAID					0
#define DISK_TYPE_SATA					1
#define DISK_TYPE_SAS					2

/*TCQ queue types*/		
#define TCQ_QUEUE_TYPE_SIMPLE			0x00
#define TCQ_QUEUE_TYPE_HDOFQUEUE		0x01
#define TCQ_QUEUE_TYPE_ORDERED			0x02
#define TCQ_QUEUE_TYPE_ACA				0x04

// Giving TargetID and LUN, returns it Type and DeviceID.  If returned Type or DeviceID is 0xFF, not found.
typedef struct    _TargetLunType
{
 MV_U8            AdapterID;
 MV_U8            TargetID;
 MV_U8            Lun;
 MV_U8            Type;            // TARGET_TYPE_LD or TARGET_TYPE_FREE_PD
 MV_U16           DeviceID;        // LD ID or PD ID depends on Type
 MV_U8            Reserved[34];
}TargetLunType, * PTargetLunType;

typedef struct	_OS_disk_info
{
	MV_U8 		ataper_id;	/* ataper disk locates */
	MV_U8 		disk_type;	/* RAID disk, SATA disk or SAS disk */
	MV_U8		queue_type; /*tcq queue types*/
	MV_U16		device_id;	/* contain target id and lun */
	MV_U16		queue_depth;	/* queue depth support this disk */
}OS_disk_info, *POS_disk_info;

#endif
