#ifndef __MV_COM_CROSS_RAID_STRUCT_H__
#define __MV_COM_CROSS_RAID_STRUCT_H__

#if !defined(_MARVELL_SDK_PACKAGE_NONRAID)

#include "com_raid_struct.h"

#ifndef _OS_BIOS
#pragma pack(8)
#endif /* _OS_BIOS */

typedef struct _Cross_VD_Info
{
 MV_U16            ID;
 MV_U8             Reserved1[6];

 MV_U64            SSDStartLBA;/* SSD start LBA in the VD */
 MV_U64            SSDEndLBA;/* SSD end LBA in the VD */          
}Cross_VD_Info, *PCross_VD_Info;

#ifndef _OS_BIOS
#pragma pack()
#endif /* _OS_BIOS */
#endif

#endif
