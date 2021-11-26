#ifndef __MV_COM_STRUCT_H__
#define __MV_COM_STRUCT_H__

#include "com_define.h"

#define GET_ALL                                 0xFF
#define ID_UNKNOWN                              0x7F

#define INVALID_ID                              0xFF	// For older driver
#define UNDEFINED_ID                            0xFFFF

//please use MV_Adapter_GetCount instead of MAX_NUM_ADAPTERS
#define MAX_NUM_ADAPTERS                        8

#ifdef _OS_BIOS
#define FREE_BLOCK(Flags)                       (Flags&(BLOCK_VALID) == Flags)
#define ASSIGN_BLOCK(Flags)                     (Flags&(BLOCK_VALID|BLOCK_ASSIGNED) == Flags)
#define INVALID_BLOCK(Flags)                    (Flags&(BLOCK_VALID|BLOCK_ASSIGNED) == 0) 
#endif /* _OS_BIOS */

#include "com_adapter_struct.h"

#include "com_pd_struct.h"
#include "com_enc_struct.h"

#include "com_dbg_struct.h"
#include "com_bbu_struct.h"

#ifndef _MARVELL_SDK_PACKAGE_NONRAID
#include "com_vd_struct.h"
#include "com_array_struct.h"
#endif

#include "com_passthrough_struct.h"
#include "com_flash_struct.h"
#include "com_smart_struct.h"

#include "com_request_header.h"
#include "com_request_detail.h"
//#include "com_ata_pass_through.h"

#endif /*  __MV_COM_STRUCT_H__ */
