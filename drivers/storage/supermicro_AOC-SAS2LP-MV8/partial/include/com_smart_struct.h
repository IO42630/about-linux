#ifndef __MV_COM_PD_SMART_STRUCT_H__
#define __MV_COM_PD_SMART_STRUCT_H__

#include "com_define.h"

#ifndef _OS_BIOS
#pragma pack(8)
#endif /* _OS_BIOS */

typedef struct _ATA_SMART
{
     MV_U8        drive_regs[7];
     MV_U8        bReserved;
     MV_U32       buffer_size;
     MV_U32       reserved;
     MV_U8        data[512];
}ATA_SMART, *PATA_SMART;

#ifndef _OS_BIOS
#pragma pack()
#endif /* _OS_BIOS */

#endif
