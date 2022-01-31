#ifndef __MV_COM_TIME_STRUCT_H__
#define __MV_COM_TIME_STRUCT_H__

#include "com_raid_struct.h"
/* the structure, refered from SCSI_SET_TIME_STAMP parameter data */
typedef struct _tm_stamp
{
	MV_U8 reserved[4];
	MV_U16 hi;
	MV_U16 mid;
	MV_U16 lw;
	MV_U8 reserved1[6];
}tm_stamp_t,*ptm_stamp_t;

#endif
