#ifndef __MV_COM_PHYSICAL_LINK_H__
#define __MV_COM_PHYSICAL_LINK_H__

#include "com_define.h"

//Physical Link
#define DEVICE_TYPE_NONE                        0
#define DEVICE_TYPE_HD                          1       //  DT_DIRECT_ACCESS_BLOCK
#define DEVICE_TYPE_PM                          2
#define DEVICE_TYPE_EXPANDER                    3		// DT_EXPANDER
#ifndef _OS_BIOS
#define DEVICE_TYPE_TAPE						4		// DT_SEQ_ACCESS
#endif
#define DEVICE_TYPE_PRINTER						5		// DT_PRINTER
#define DEVICE_TYPE_PROCESSOR					6		// DT_PROCESSOR
#define DEVICE_TYPE_WRITE_ONCE					7 		// DT_WRITE_ONCE
#define DEVICE_TYPE_CD_DVD						8		// DT_CD_DVD
#define DEVICE_TYPE_OPTICAL_MEMORY				9 		// DT_OPTICAL_MEMORY
#define DEVICE_TYPE_MEDIA_CHANGER				10		// DT_MEDIA_CHANGER
#define DEVICE_TYPE_ENCLOSURE					11		// DT_ENCLOSURE
#define DEVICE_TYPE_I2C_ENCLOSURE				12		
#define DEVICE_TYPE_PORT                        0xFF	// DT_STORAGE_ARRAY_CTRL

#define MAX_WIDEPORT_PHYS                       8

#ifndef _OS_BIOS
#pragma pack(8)
#endif /* _OS_BIOS */
typedef struct _Link_Endpoint 
{
 MV_U16      DevID;
 MV_U8       DevType;         /* Refer to DEVICE_TYPE_xxx */
 MV_U8       PhyCnt;          /* Number of PHYs for this endpoint. Greater than 1 if it is wide port. */
 MV_U8       PhyID[MAX_WIDEPORT_PHYS];    /* Assuming wide port has max of 8 PHYs. */
 MV_U8       SAS_Address[8];  /* Filled with 0 if not SAS device. */
 MV_U16      EnclosureID;     // enclosure ID of this device if available, otherwise 0xFFFF
 MV_U8       Reserved[6];
} Link_Endpoint, * PLink_Endpoint;

typedef struct _Link_Entity 
{
 Link_Endpoint    Parent;
 MV_U8            Reserved[8];
 Link_Endpoint    Self;
} Link_Entity,  *PLink_Entity;

#ifndef _OS_BIOS
#pragma pack()
#endif /* _OS_BIOS */

#endif
