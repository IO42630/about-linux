#ifndef __MV_COM_ENTRIES_STRUCT_H__
#define __MV_COM_ENTRIES_STRUCT_H__

typedef struct _Hypper_LBAEntry
{
	MV_U64    lba;
	MV_U32    length;
	MV_U32    reserved;
}Hypper_LBAEntry,*PHypper_LBAEntry;

#define EMPTY_ENTIES                              0x0

typedef struct _Hypper_Entry_Table
{
	MV_U16   TotalCount;
	MV_U16   RemainCount;
	MV_U8    reserved[36];
}Hypper_Entry_Table,*PHypper_Entry_Table;

#endif
