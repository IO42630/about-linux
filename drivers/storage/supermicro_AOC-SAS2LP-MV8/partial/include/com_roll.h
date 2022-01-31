#ifndef COM_ROLL_H
#define COM_ROLL_H

#ifdef RAID_ERROR_HANDLING

#define ROLL_RESOURCE_TYPE_CONTEXT		MV_BIT(0)
#define ROLL_RESOURCE_TYPE_RANGE		MV_BIT(1)
#define ROLL_RESOURCE_TYPE_SGTABLE		MV_BIT(2)

typedef struct _EH_RANGE
{
	struct _EH_RANGE	*next;
	MV_LBA				Bad_Lba;
	MV_U32				Bad_Sectors;
}EH_RANGE, *PEH_RANGE;

/* The original data saved during the rollover. */
typedef struct _ROLL_ORG
{
	struct _ROLL_ORG	*next;
	MV_SG_Table			SG_Table;			/* Original SG Table */
	MV_LBA				Org_LBA;
	MV_U32				Org_Sector;
	MV_U8				Org_Cdb;			/* Original Cdb [0] */
	MV_U8				reserved[3];
}ROLL_ORG, *PROLL_ORG;

/* Resource management function:
 * context is the module extension.
 * pResource is valid if allocate = MV_FALSE.
 * resourceType is defined as ROLL_RESOURCE_TYPE_XXX
 * allocate is a MV_BOOLEAN variable. 
 * When it is MV_TRUE, the function is called to allocate resource. 
 * When it is MV_FALSE, the function is called to release the resource specified by pResource. */
typedef MV_PVOID (*Roll_ResourceManager) (MV_PVOID context, MV_PVOID pResource, MV_U8 resourceType, MV_BOOLEAN allocate);

#define ROLL_FLAG_NONE					0
#define ROLL_FLAG_VALID_ORG_DATA		MV_BIT(0)
#define ROLL_FLAG_SHRINK_SIZE			MV_BIT(1)

typedef struct _ROLL_CTX
{
	List_Head			Queue_Pointer;

	/* Fixed variables */	
	MV_PVOID			Module_Ext;			/* Module Extension */
	MV_U32				Completed_Sector;	/* Completed Sector Count */
	MV_U8				Flag;				/* ROLL_FLAG_XXX */
	MV_U8				Reserved0[3];

	/* Resource will be allocated on demand */
	PROLL_ORG			pRoll_Org;			/* MV_Request Original Variables */
	PEH_RANGE			pEH_Range;			/* Error Ranges have been hit */

	/* Function Tables */
	Roll_ResourceManager	pFResourceManager;	/* Function used to allocate and release resource. */
}ROLL_CTX, * PROLL_CTX;

typedef enum _ROLL_ACTION{
	ROLL_ACTION_ADJUST_SIZE	= 0,	/* Won't roll the request. Just adjust request size. 
									 * After that, the following rollover will try the whole left size. */
	ROLL_ACTION_SKIP		= 1,	/* Skip the current range and record error. Then continue the left range. */
	ROLL_ACTION_CONTINUE	= 2,	/* Continue the left range */
	ROLL_ACTION_CHANGE_CDB	= 3,	/* Change CDB code. So far just supports from R/W to Verify. */
	ROLL_ACTION_SHRINK_SIZE = 4		/* Won't roll the request. Just adjust request size. 
									 * After that, the following rollover will try the size less/equal to this size. */

} ROLL_ACTION;


/* Initialize the rollover request. */
MV_VOID Rollover_Init(
	PMV_Request pMvReq,
	MV_PVOID pModuleExt,
	Roll_ResourceManager pFResource
	);

/* Cleanup the rollover request. */
MV_VOID Rollover_Cleanup(
	PMV_Request pMvReq
	);

/* Four actions.	
 * ROLL_ACTION_ADJUST_SIZE and ROLL_ACTION_SHRINK_SIZE: Won't roll the request. Just adjust request size.
 * The difference between them is the following ROLL_ACTION_CONTINUE.
 * For ROLL_ACTION_ADJUST_SIZE, continue will try the whole left size.
 * For ROLL_SHRINK_SIZE, continue will try size less or equal to the adjusted size.
 * ROLL_ACTION_SKIP:Skip the current range and record error. Then continue the left range.
 * ROLL_ACTION_CONTINUE: Continue the left range
 * pMvReq and action must be specified for all actions.
 * size is only used for ROLL_ACTION_ADJUST_SIZE and ROLL_ACTION_SHRINK_SIZE.
 * isFinished indicated whether the request is already finished.
 * MV_TRUE means this time, no access range is left to handle.
 */
MV_VOID Rollover_Roll(
	PMV_Request pMvReq,
	ROLL_ACTION action,
	MV_U32		size,
	MV_BOOLEAN  *isFinished
	);

/* Whether ever did Rollover_Roll three actions before. */
MV_BOOLEAN Rollover_HasRolled(
	PMV_Request pMvReq
	);

/* Whether has skipped ranges. */
#define Rollover_HasEHRange(pMvReq)	\
((pMvReq)->Roll_CTX!=NULL) ? ((PROLL_CTX)((pMvReq)->Roll_CTX))->pEH_Range!=NULL?MV_TRUE:MV_FALSE : MV_FALSE

/* Copy the EH Range. */
MV_VOID Rollover_CopyEHRange(
	PMV_Request pDestReq,
	PMV_Request pSourceReq
	);

MV_VOID Rollover_CleanEHRange(
	PMV_Request pMvReq
	);

MV_VOID Rollover_AddEHRange(
	PMV_Request	pMvReq,
	MV_LBA		lba,
	MV_U32		sector
	);

/* Returned the skipped ranges.*/
#define Rollover_GetEHRange(pMvReq) ((pMvReq)->Roll_CTX!=NULL)?((PROLL_CTX)((pMvReq)->Roll_CTX))->pEH_Range:NULL

MV_U8 Rollover_GetOriginalCDB(
	PMV_Request pMvReq
	);

#endif /* RAID_ERROR_HANDLING */

#endif /* COM_ROLL_H */
