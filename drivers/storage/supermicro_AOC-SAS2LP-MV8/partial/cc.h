#ifndef _MODULE_CC_H
#define _MODULE_CC_H

/*
 * Here is the definition for the command consolidate sub module
 * This is only changed when we modify the consolidate algorithm.
 */
typedef struct _Consolidate_Object
{
	MV_LBA Last_LBA;                                    /* last LBA*/
	PMV_Request Holding_Request;                        /* Internal request which already consolidate some external requests. */
	MV_U8 Sequential;                                   /* sequential counter */
	MV_BOOLEAN Is_Read;                                 /* The last request is read or write. */
	MV_U16 io_count;
	MV_BOOLEAN	Enable_Consolidate;	/* If consolidation is enalbed on this device */
	MV_U8	Cons_SG_Count;		/* Consolidation SG Count */										/* (SG Count of cache request is different from core request) */
	MV_U8	Cons_Req_Count;
	MV_U8	Reserved;
} Consolidate_Object, *PConsolidate_Object;

typedef struct _ModConsolidate_Extension
{
	List_Head Free_Queue;
	PConsolidate_Object pConsolid_Obj;
	MV_PVOID pUpperExtension;
	MV_PVOID pNextExtension;
	MV_VOID (*pNextFunction) (MV_PVOID, PMV_Request);
	MV_U16 dev_count;
	MV_BOOLEAN ModCons_Enabled;		/* 1 - module consolidation is enabled on the adapter */
	MV_U8 Reserved0;
} ModConsolidate_Extension, *PModConsolidate_Extension;

/*============= Consolidate usage ==========================
step:
	1. call "Consolid_GetResourceQuota" to get resource 	requirement of Consolidate.
	2. call "Consolid_InitializeExtension" to initial resource of Consolidate.
	3. call "Consolid_SetSendFunction" to set executing function of Consolidate.
	4. call "Consolid_ModuleSendRequest" to process your request.
	5. call "Consolid_PushFireRequest" to chech if holding request need to push.

========================================================*/
MV_U32 ModConsolid_GetResourceQuota(
		MV_U16 reqCount,
		MV_U16 DevCount,
		MV_U16 sgCount);

void ModConsolid_InitializeExtension(
		MV_PVOID This,
		MV_U16 reqCount,
		MV_U16 devCount,
		MV_U16 sgCount);

void ModConsolid_SetSendFunction(
		MV_PVOID This,
		MV_PVOID current_ext,
		MV_PVOID next_ext,
		MV_VOID (*next_function) (MV_PVOID, PMV_Request));

void ModConsolid_ModuleSendRequest(MV_PVOID This, PMV_Request pReq);
void ModConsolid_PushFireRequest(MV_PVOID This, PMV_Request pReq);
void ModConsolid_SetDevice(MV_PVOID This, struct mod_notif_param *p_notify);
void ModConsolid_InitConsDev(MV_PVOID p_module);
#endif
