#ifndef COM_EVENT_DRIVER_H
#define COM_EVENT_DRIVER_H

#ifndef COM_DEFINE_H //for magni not use include com_define to define MV_U32
#include "com_define.h"
#endif

#define MAX_EVENTS                      20
#define MAX_EVENTS_WAITED	  	16
#define MAX_EVENT_PARAMS                4
#define MAX_EVENTS_RETURNED             6
#define MAX_EVENT_SENSE_DATA_COUNT	30

#ifndef _OS_BIOS
#pragma pack(8)
#endif /*  _OS_BIOS */

#if defined(_OS_FIRMWARE)
typedef struct _HotPlugEvent
{
	MV_U16	size;
	MV_U8	dummy[2];
	MV_U8	bitmap[0];
}HotPlugEvent;
#endif

typedef struct _DriverEvent
{
	MV_U32  TimeStamp;
	MV_U32  SequenceNo; /* (contiguous in a single adapter) */
	MV_U32  EventID;    /* 1st 16 bits - Event class */
                        /* last 16 bits - Event code of this particula Event class */
	MV_U8   Severity;
	MV_U8   AdapterID; /*For LokiPlus, the byte will use to check whether event is vaild or not. If yes, it will be added to systme event log.*/
	MV_U16  DeviceID;   /* Device ID relate to the event class (HD ID, LD ID etc) */
	MV_U32  Params[MAX_EVENT_PARAMS]; /* Additional information if ABSOLUTELY necessary. */
} DriverEvent, * PDriverEvent;

typedef struct _EventRequest
{
	MV_U8        Count; /* [OUT] # of actual events returned */
	MV_U8        Reserved[3];
	DriverEvent  Events[MAX_EVENTS_RETURNED];
} EventRequest, * PEventRequest;

// Event support sense code
typedef struct _DriverEvent_V2
{
    DriverEvent  Event;                /* same as the current one */
    MV_U8        SenseDataLength;      /* actual length of SenseData.  Driver set it to 0 if no SenseData */
    MV_U8        accurated;
    MV_U8        SenseData[30];        /* (24+6) just for making this structure on 64-bits boundary */
} DriverEvent_V2, * PDriverEvent_V2;

typedef struct _EventRequest_V2
{
    MV_U8           Count; /* [OUT] # of actual events returned */
    MV_U8           Reserved[3];
    DriverEvent_V2  Events[MAX_EVENTS_RETURNED];
} EventRequest_V2, * PEventRequest_V2;


#define EVENTL0G_HEAD_SIGNATURE                "TLEM"
#define EVENTLOG_HEAD_RESERVED_BYTES      16
#define EVENTLOG_ENTRY_VALID                        0x00000001L

#if defined(SUPPORT_NVRAM) && defined(_OS_FIRMWARE)
#define NVRAM_START_OFFSET			0

struct nvram_event_log_head
{
	MV_U8	signature[4];
	MV_U32	next_tbl_off;
	MV_U16	version;
	MV_U16  	nr_max_entries;
	MV_U32  	crc;
	MV_U8  	reserved[EVENTLOG_HEAD_RESERVED_BYTES];
};

struct nvram_event_log
{
	struct nvram_event_log_head head;
	MV_U32	sequence_no;
	MV_U16	valid_slot_start;
	MV_U16	valid_slot_end;
	MV_U32	reserved;
	MV_U32 	log_crc;
};

struct nvram_normal_head
{
	MV_U8	signature[4];
	MV_U32	next_tbl_off;
	MV_U16	version;
	MV_U16  	nr_max_entries;
	MV_U32  	crc;
	MV_U8  	reserved[16];
};
#endif /*SUPPORT_NVRAM*/

#ifndef _OS_BIOS
#pragma pack()
#endif /*  _OS_BIOS */

#endif /*  COM_EVENT_DRIVER_H */
