#ifndef _HBA_API_H
#define _HBA_API_H
typedef struct _RAID_Feature
{
	List_Head Internal_Request;
	MV_PVOID pHBA;
	MV_PVOID pUpperExtension;
	MV_PVOID pNextExtension;
	MV_VOID (*pNextFunction) (MV_PVOID, PMV_Request);
	MV_U16 SMART_Status_Timer_Handle;
	MV_U8 reserved[2];

} RAID_Feature, *PRAID_Feature;

MV_U32 RAID_Feature_GetResourceQuota(MV_U16 maxIo);
void RAID_Feature_Initialize(MV_PVOID This, MV_U16 maxIo);
void RAID_Feature_SetSendFunction( MV_PVOID This,
	MV_PVOID current_ext,
	MV_PVOID next_ext,
	MV_VOID (*next_function) (MV_PVOID, PMV_Request));
void mvSetAdapterConfig( MV_PVOID This, PMV_Request pReq);
void mvGetAdapterConfig( MV_PVOID This, PMV_Request pReq);
#endif
