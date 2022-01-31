#ifndef __MV_COM_PHY_STRUCT_H__
#define __MV_COM_PHY_STRUCT_H__

#include "com_define.h"

#ifndef _OS_BIOS
#pragma pack(8)
#endif /* _OS_BIOS */

typedef struct _NEW_PHY_TUNING {
         MV_U8    Trans_Emphasis_En:1;                    /* 1 bit,  transmitter emphasis enable  */
         MV_U8    Reserved_bit_1:3;                       /* 3 bits, reserved space */
         MV_U8    Trans_Emphasis_Amp:4;                   /* 4 bits, transmitter emphasis amplitude */

         MV_U8    Trans_Amp:5;                            /* 5 bits, transmitter amplitude */
         MV_U8    Reserved_bit_2:3;                       /* 3 bits, reserved space */

         MV_U8    Trans_Amp_Adjust:2;                     /* 2 bits, transmitter amplitude adjust */
         MV_U8    Reserved_bit_3:6;                       /* 6 bit,    reserved space */
         
         MV_U8    Reserved;                               /* 1 bytes, reserved space */
} NEW_PHY_TUNING, *PNEW_PHY_TUNING;

typedef struct _PHY_TUNING_CONFIG {
         NEW_PHY_TUNING Value;
         MV_U8    Gen_Speed;                              /* 1: Gen1; 2:Gen2; 3: Gen3 */
         MV_U8    reserved[3];
} MV_PHY_TUNING_CONFIG;

typedef union {
    struct {
        MV_U32 low;
        MV_U32 high;
    } parts;
    MV_U8       b[8];
    MV_U16      w[4];
    MV_U32      d[2];        
} MV_SAS_ADDR;

typedef union {
    MV_PHY_TUNING_CONFIG tuning;
    MV_SAS_ADDR          sas; 
} PHY_CONFIG, *PPHY_CONFIG;

#ifndef _OS_BIOS
#pragma pack()
#endif /* _OS_BIOS */

#endif
