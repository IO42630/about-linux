#ifndef __MV_ATA_PASS_THROUGH_STRUCT_H__
#define __MV_ATA_PASS_THROUGH_STRUCT_H__

#include "com_define.h"

#ifndef _OS_BIOS
#pragma pack(8)
#endif /* _OS_BIOS */

typedef struct _ATA_REGS
{
	MV_U8     drive_regs[7];
	MV_U8     bReserved;
	MV_U16    buffer_size;
	MV_U8     reserved[6];
	MV_U8     data[1];
}ATA_REGS,*PATA_REGS;

#ifndef _OS_BIOS
#pragma pack()
#endif /* _OS_BIOS */

#endif
