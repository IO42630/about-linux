#ifndef __HBA_TIMER_H__
#define __HBA_TIMER_H__

#include "com_tag.h"
#include "hba_exp.h"

enum _tag_hba_msg_state{
	MSG_QUEUE_IDLE=0,
	MSG_QUEUE_PROC,
	MSG_QUEUE_NO_START
};

struct mv_hba_msg {
	MV_PVOID data;
	MV_U32   msg;
	MV_U32   param;
	List_Head msg_list;
};

struct mv_hba_msg_queue {
	spinlock_t lock;
	List_Head free;
	List_Head tasks;
	struct mv_hba_msg msgs[MSG_QUEUE_DEPTH];
};

enum {
	HBA_TIMER_IDLE = 0,
	HBA_TIMER_RUNNING,
	HBA_TIMER_LEAVING,
};
void hba_house_keeper_init(void);
void hba_house_keeper_run(void);
void hba_house_keeper_exit(void);
void hba_msg_insert(void *data, unsigned int msg, unsigned int param);
void hba_init_timer(PMV_Request req);
void hba_remove_timer(PMV_Request req);
void hba_remove_timer_sync(PMV_Request req);
void hba_add_timer(PMV_Request req, int timeout,
		   MV_VOID (*function)(MV_PVOID data));
extern struct mv_lu *mv_get_device_by_target_lun(struct hba_extension *hba, MV_U16  target_id, MV_U16 lun);
extern struct mv_lu *mv_get_avaiable_device(struct hba_extension * hba, MV_U16 target_id, MV_U16 lun);
extern MV_U16 get_id_by_targetid_lun(MV_PVOID ext, MV_U16 id,MV_U16 lun);

#if  defined(__VMKLNX__) || defined (MV_VMK_ESX35)
/*vmware use 100 for HZ*/
#define TIMER_INTERVAL_OS		100		/* 10 millisecond */
#define TIMER_INTERVAL_LARGE_UNIT	50		/* 10 millisecond */
#define TIMER_INTERVAL_SMALL_UNIT	10		/* 10 millisecond */
#else
#define TIMER_INTERVAL_OS		1000		/* millisecond */
#define TIMER_INTERVAL_LARGE_UNIT	500		/* millisecond */
#define TIMER_INTERVAL_SMALL_UNIT	100		/* millisecond */
#endif

#endif /* __HBA_TIMER_H__ */


