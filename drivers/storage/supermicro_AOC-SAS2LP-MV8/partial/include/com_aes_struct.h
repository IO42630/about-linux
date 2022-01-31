#ifndef __MV_COM_AES_STRUCT_H__
#define __MV_COM_AES_STRUCT_H__

#include "com_define.h"

#define MAX_SUPPORT_AES_SATA_PORT	4 /*4:9230, 9236 2:9220*/
#define AES_KEY_SPI_ENTRY_NUMBER    10 // total entry number for user use

#define AES_KEY_CONTENT_LENGTH                 32

#define MV_AES_KEY_CLEAR                   0
#define MV_AES_KEY_128                     16
#define MV_AES_KEY_256                     32
#define MV_AES_KEY_PERSIST                 0xFF

#ifndef _OS_BIOS
#pragma pack(8)
#endif /* _OS_BIOS */

typedef struct _aes_entry_info
{
    MV_U8 aes_port[MAX_SUPPORT_AES_SATA_PORT][2]; // supply current port id and aes entry
    MV_U8 entry[AES_KEY_SPI_ENTRY_NUMBER]; // available / not available
    MV_U8 reserved[2];
}aes_entry_info,*Paes_entry_info;

typedef struct _entry_link
{
    MV_U8       port_id;
    MV_U8       entry;
    MV_U8       reserved[6];                            // for 64 bit align
    MV_U8       user_auth[AES_KEY_CONTENT_LENGTH];      // user authentication key 32 bytes.
} entry_link, *Pentry_link;

typedef struct _AES_Entry_Config {
    MV_U8       entry_id;                               //SPI entry 0~9
    MV_U8       key_length;                             //0: remove, 16: 128bit, 32: 256bit, 0xFF: no change
    MV_U8       reserved[6];                            // for 64 bit align
    MV_U8       key_content[AES_KEY_CONTENT_LENGTH];    // Fill up 128 bit or 256 bit key.
    MV_U8       user_auth[AES_KEY_CONTENT_LENGTH];      // user authentication key 32 bytes.
} AES_Entry_Config, *PAES_Entry_Config;

typedef struct _AES_Port_Config{
    MV_U8       port_id;
    MV_BOOLEAN  aes_enable;
    MV_U8       reserved[6];
} AES_Port_Config, *PAES_Port_Config;

typedef struct _AES_Entry_Verify {
    MV_U8       entry_id;                               //SPI entry 0~9
    MV_U8       key_length;                             //16: 128bit, 32: 256bit
    MV_U8       reserved[6];                            // for 64 bit align
    MV_U8       key_content[AES_KEY_CONTENT_LENGTH];    // Fill up 128 bit or 256 bit key.
    MV_U8       user_auth[AES_KEY_CONTENT_LENGTH];      // user authentication key 32 bytes.
} AES_Entry_Verify, *PAES_Entry_Verify;

typedef struct _AES_Change_Passwd {
    MV_U8       entry_id;                               // SPI entry 0~9
    MV_U8       reserved[7];                            // for 64 bit align
    MV_U8       old_user_auth[AES_KEY_CONTENT_LENGTH];  // user authentication key 32 bytes.
    MV_U8       new_user_auth[AES_KEY_CONTENT_LENGTH];  // user authentication key 32 bytes.
} AES_Change_Passwd, *PAES_Change_Passwd;

typedef struct _AES_PORT_INFO
{
    MV_U8       id;
    MV_U8       entry;
    MV_U8       Reserved[6]; //Align to 64bits
} AES_PORT_INFO, *PAES_PORT_INFO;

#define AES_ENTRY_STATUS_AVAILABLE           1
#define AES_ENTRY_STATUS_NOT_AVAILABLE       0

typedef struct _AES_KEY_ENTRY_INFO
{
    MV_U8        id;
    MV_U8        status;//AES_ENTRY_STATUS_XXXXXX
    MV_U8        Reserved[6]; //Align to 64bits
} AES_KEY_ENTRY_INFO, *PAES_KEY_ENTRY_INFO;

#ifndef _OS_BIOS
#pragma pack()
#endif /* _OS_BIOS */

#endif
