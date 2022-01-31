#ifndef __MV_COM_DBG_STRUCT_H__
#define __MV_COM_DBG_STRUCT_H__

#include "com_define.h"

#ifndef _OS_BIOS
#pragma pack(8)
#endif /* _OS_BIOS */

// Type of request for which the error should trigger.
#define DBG_REQUEST_READ                        MV_BIT(0)
#define DBG_REQUEST_WRITE                       MV_BIT(1)
#define DBG_REQUEST_VERIFY                      MV_BIT(2)


// The following data structure is dynamically allocated.  Depends on
// NumSectors, the total size of the data structure should be
// (8 + 4 + (SECTOR_LENGTH * NumSectors))
// Where 8 is the size of LBA and 4 is the size of NumSectors itself.
typedef struct _DBG_DATA
{
	MV_U64            LBA;
	MV_U32            NumSectors;
	MV_U8             Data[1];
}DBG_Data, *PDBG_Data;

typedef struct _DBG_HD
{
	MV_U64            LBA;
	MV_U16            HDID;
	MV_BOOLEAN        isUsed;
	MV_U8             Reserved[5];
}DBG_HD;

typedef struct _DBG_FLASH
{
	MV_U32            OffSet;
	MV_U16            NumBytes;
	MV_U8             Data[1];
}DBG_Flash, *PDBG_Flash;

typedef struct _DBG_NVSRAM
{
	MV_U32     Offset;
	MV_U16     NumBytes;
	MV_U16     ReturnedCount;
	MV_U8      Reserved[8];
	MV_U8      Data[256];
}DBG_NVSRAM, *PDBG_NVSRAM;

// Map to/from VD LBA to/from PD LBA
typedef struct _DBG_MAP
{
	MV_U64            VD_LBA;
	MV_U64            PD_LBA;
	MV_U16            VDID;          // if 'mapDirection' is DBG_PD2VD, set it to 0xFFFF as input and driver will return the mapped VD ID
	MV_U16            PDID;          // must specified in any case
	MV_BOOLEAN        parity;        // [out](true or false) if 'mapDirection' is DBG_VD2PD, this tells if the specified PD is a parity disk or not.
	MV_U8             mapDirection;  // DBG_VD2PD or DBG_PD2VD
	MV_U8             Reserved[34];
}DBG_Map, *PDBG_Map;

typedef struct _DBG_Error_Injection
{
	MV_U64     LBA;
	MV_U32     Count;
	MV_U16     HDID;
	MV_U8      Error_case;
	MV_U8      Error_Status;
	MV_U8      Request_Type;
	MV_U8      Sense_idx;
	MV_U8      Reserved[6];
}DBG_Error_Injection, *PDBG_Error_Injection;

#define DBG_VD2PD                               0
#define DBG_PD2VD                               1

#ifndef _OS_BIOS
#pragma pack()
#endif /* _OS_BIOS */
#endif
