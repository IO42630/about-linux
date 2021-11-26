#ifndef __MV_COM_FLASH_STRUCT_H__
#define __MV_COM_FLASH_STRUCT_H__

#include "com_define.h"

#define 	 FLASH_DOWNLOAD                 0xf0
#define	 FLASH_UPLOAD                       0xf

//for read/write flash test command
#define  FLASH_BYTE_WRITE           0
#define  FLASH_BYTE_READ            1

#define    FLASH_TYPE_CONFIG           0
#define    FLASH_TYPE_BIN              1
#define    FLASH_TYPE_BIOS             2
#define    FLASH_TYPE_FIRMWARE         3
#define    FLASH_TYPE_AUTOLOAD         4	
#define    FLASH_TYPE_NVSRAM           5
#define    FLASH_TYPE_RAW              6 // the data is an image with header. as same as firmware. design for autoload,configure. oem only


#define 	FLASH_ERASE_PAGE                      0x1  //Erase bios or PD page or hba info page
#define	FLASH_PD_PAGE					1	// Erase PD page in flash memory but not in-uses PD id 
#define	FLASH_PD_PAGE_FORCE			254	// Force to erase the whole PD page even PD id is in-use. Used by manufacturing only!

typedef struct _MV_FLASH_PER_DATA{
	MV_U8    image_type;
	MV_U8    reserved[3];
	MV_U32   image_size;
} MV_FLASH_PER_DATA, *PMV_FLASH_PER_DATA;

#endif
