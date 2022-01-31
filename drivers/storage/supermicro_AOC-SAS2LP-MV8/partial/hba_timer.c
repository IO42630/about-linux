#include "hba_header.h"
#include "hba_exp.h"
#include "hba_mod.h"
#include "hba_timer.h"

/* how long a time between which should each keeper work be done */
#define KEEPER_SHIFT (HZ >> 1)

static struct mv_hba_msg_queue mv_msg_queue;

#if !defined(SUPPORT_WORKQUEUE) || (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0))
static struct task_struct *house_keeper_task = NULL;
#endif

static int shutdown = 0;
static int __msg_queue_state;

static inline int queue_state_get(void)
{
	return __msg_queue_state;
}

static inline void queue_state_set(int state)
{
	__msg_queue_state = state;
}
MV_U8 pal_set_down_disk_from_upper(void *ext, MV_U16 device_target_id, MV_U16 device_lun);
MV_U8 pal_check_disk_exist(void *ext, MV_U16 device_target_id, MV_U16 device_lun);
static void hba_proc_msg(struct mv_hba_msg *pmsg)
{
	PHBA_Extension phba;
	struct scsi_device *psdev=NULL;
	struct mv_adp_desc *hba_desc;
	struct mv_lu *lu = NULL; 
	MV_U16 dev_id;
	MV_U16 dev_lun = (MV_U16)(pmsg->param>>16)&0xffff;
	unsigned long flags;
	/* we don't do things without pmsg->data */
	if (NULL == pmsg->data){
		MV_DPRINT(( "__MV__ In hba_proc_msg pmsg->data == NULL return.\n"));
		return;
	}

#ifdef MV_VMK_ESX35
	/* not support  */
	return;
#endif
	phba = (PHBA_Extension) pmsg->data;
	hba_desc= phba->desc->hba_desc;
	dev_id = (MV_U16)pmsg->param;	//low word target ID
	dev_lun = (MV_U16)(pmsg->param>>16)&0xffff;	// high word LUN
	lu = mv_get_device_by_target_lun(phba, dev_id, dev_lun);
	MV_DPRINT(( "__MV__ In hba_proc_msg.\n"));

	MV_ASSERT(pmsg);
	MV_ASSERT(phba->desc->hba_desc->hba_host);

	switch (pmsg->msg) {
	case EVENT_DEVICE_ARRIVAL:
		if(lu == NULL)
			lu = mv_get_avaiable_device(phba, dev_id, dev_lun);
		if (lu == NULL){
			MV_ASSERT(lu != NULL);
			return;
		}
		if ( lu->sdev ) {
			MV_DPRINT(( "__MV__ add scsi disk %d-%d-%d failed, it existed.\n", 0, dev_id, dev_lun));
			break;
		}
#ifdef __VMKLNX__
		psdev = __scsi_add_device(hba_desc->hba_host, 0, dev_id, dev_lun, 0);
		if (IS_ERR(psdev)) {
			MV_DPRINT(( "__MV__ add scsi disk %d-%d-%d failed.\n", 0, pmsg->param, 0));
		} else {
			MV_DPRINT(( "__MV__ add scsi disk %d-%d-%d.\n", 0, pmsg->param, 0));
			scsi_device_put(psdev);
		}
#else		
		if (scsi_add_device(hba_desc->hba_host, 0, dev_id, dev_lun)) {
			MV_DPRINT(( "__MV__ add scsi disk %d-%d-%d failed.\n", 0, dev_id, dev_lun));
			if (hba_desc->RunAsNonRAID) {
				spin_lock_irqsave(&hba_desc->global_lock, flags);
				pal_set_down_disk_from_upper(phba, dev_id, dev_lun);
				spin_unlock_irqrestore(&hba_desc->global_lock, flags);
			}
			else
				MV_ASSERT(0);
		} else {
			MV_DPRINT(( "__MV__ add scsi disk %d-%d-%d.\n", 0, dev_id, dev_lun));
		}
#endif
		break;
	case EVENT_DEVICE_REMOVAL:	
		if (lu == NULL){
			MV_ASSERT(lu != NULL);
			return;
		}
		psdev = lu->sdev;
#ifdef __VMKLNX__
		if (!psdev)
			psdev = scsi_device_lookup(hba_desc->hba_host, 0, lu->target_id, 0);
#endif
 		if ( psdev ) {
	 		if ( scsi_device_get(psdev) != 0 ) {
				WARN_ON(1);
				MV_DPRINT(("__MV__ no disk to remove %d-%d-%d\n", 0, psdev->id, psdev->lun));
				psdev = NULL;
			}
 		}		
 		if ( psdev) {
			MV_DPRINT((  "__MV__ remove scsi disk %d-%d-%d.\n", 0,psdev->id, psdev->lun));
			scsi_remove_device(psdev);
			scsi_device_put(psdev);
		}
		break;
	default:
		break;
	}
}
MV_U8	need_rescan = MV_FALSE;
void *rescan_hba=NULL;

int	hba_scan_host(void)
{
	MV_U32 target=0, lun=0;
	int res= 0;
	struct mv_lu * lu=NULL;
	PHBA_Extension phba;
	unsigned long flags;
	spin_lock_irqsave(&mv_msg_queue.lock, flags);
	if ((need_rescan == MV_FALSE) || !rescan_hba) {
		spin_unlock_irqrestore(&mv_msg_queue.lock, flags);
		return 0;
	}
	phba = (PHBA_Extension)rescan_hba;
	need_rescan = MV_FALSE;
	rescan_hba = NULL;
	spin_unlock_irqrestore(&mv_msg_queue.lock, flags);

	if (!phba->RunAsNonRAID){
		//TBD, raid driver not support.
		return 0;
	}
	
	MV_DPRINT(("start scan host.\n"));
	for (target =0; target < MV_MAX_TARGET_NUMBER; target++) {
		lu = mv_get_device_by_target_lun(phba, target, lun);	//TBD single lun 
		res = pal_check_disk_exist(phba, target, lun);
		if (res && (!lu || !lu->sdev)){
			MV_DPRINT(("device %d-%d has added.\n", target, lun));
			hba_msg_insert(phba, EVENT_DEVICE_ARRIVAL, target | (lun << 16));
		} else if (!res && (lu && lu->sdev)){
			MV_DPRINT(("device %d-%d has gone.\n", target, lun));
			hba_msg_insert(phba, EVENT_DEVICE_REMOVAL, target | (lun << 16));
		}
	}
	MV_DPRINT(("finshed scan host.\n"));
	return 0;
	
}


static void mv_proc_queue(void)
{
	struct mv_hba_msg *pmsg;
	unsigned long flags;

	/* work on queue non-stop, pre-empty  */
	queue_state_set(MSG_QUEUE_PROC);

	while (1) {
		MV_DPRINT((  "__MV__ process queue starts.\n"));
		spin_lock_irqsave(&mv_msg_queue.lock, flags);
		if (List_Empty(&mv_msg_queue.tasks)) {
			/* it's important we put queue_state_set here. */
			queue_state_set(MSG_QUEUE_IDLE);
			spin_unlock_irqrestore(&mv_msg_queue.lock, flags);
			MV_DPRINT((  "__MV__ process queue ends.\n"));
			break;
		}
		pmsg = LIST_ENTRY(mv_msg_queue.tasks.next, struct mv_hba_msg, msg_list);
		spin_unlock_irqrestore(&mv_msg_queue.lock, flags);
		if (NULL == pmsg) {
			MV_DPRINT((   "__MV__ pmsg == NULL .\n"));
			return;
		}
		hba_proc_msg(pmsg);
		/*clean the data before returning it to free list*/
		pmsg->data = NULL;

		spin_lock_irqsave(&mv_msg_queue.lock, flags);
		List_MoveTail(&pmsg->msg_list, &(mv_msg_queue.free));
		spin_unlock_irqrestore(&mv_msg_queue.lock, flags);
		MV_DPRINT((  "__MV__ process queue ends.\n"));
	}
	hba_scan_host();
}

static inline MV_U32 hba_msg_queue_empty(void)
{
	return List_Empty(&(mv_msg_queue.tasks));
}


#ifndef SUPPORT_WORKQUEUE
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,0)
static int hba_house_keeper(void *data)
{
	set_user_nice(current, -15);
	MV_DPRINT((  "Enter House keeper!\n"));
	while (!kthread_should_stop()) {
		if (!hba_msg_queue_empty() &&
			MSG_QUEUE_IDLE == queue_state_get()) {
			MV_DPRINT((  "mv_proc_queue runing.\n"));
			mv_proc_queue();
		}
		MV_DPRINT(("House keeper sleep!\n"));
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
		__set_current_state(TASK_RUNNING);
		MV_DPRINT((  "House keeper wake up!\n"));
	}
	return 0;
}
#else
/*Marvell hotplug kernel thread.*/
struct completion marvell_hp_completion;
long marvell_hp_thread_id = 0;
DECLARE_WAIT_QUEUE_HEAD(wait_queue);
static int hba_house_keeper(void *data)
{
	DECLARE_WAITQUEUE(wait, current);
	siginitsetinv(&current->blocked, 0);
	sprintf(current->comm, "mv64xx_hp");
	/* Flush resources */
	daemonize();
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,9)
	reparent_to_init();
#endif
	init_completion(&marvell_hp_completion);
	set_current_state(TASK_UNINTERRUPTIBLE);
	add_wait_queue(&wait_queue,&wait);
	while(1){
		if(shutdown == 1)
			break;
                if (!hba_msg_queue_empty() &&
                    MSG_QUEUE_IDLE == queue_state_get()) {
                        mv_proc_queue();
                }
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule();
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(&wait_queue,&wait);
	complete(&marvell_hp_completion);
	return 0;
}
#endif

#endif

#ifdef SUPPORT_WORKQUEUE

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,13)

#ifdef TIMER_INITIALIZER
#undef TIMER_INITIALIZER
#endif
#define TIMER_INITIALIZER(_function, _expires, _data) {		\
		.function = (_function),		\
		.expires = (_expires),			\
		.data = (_data),				\
		.base = NULL,					\
		.magic = TIMER_MAGIC,		\
	}

#endif


#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,20)
static void mv_wq_handler(void *work)
#else
static void mv_wq_handler(struct work_struct *work)
#endif
{
	if (hba_msg_queue_empty()) {
		MV_DPRINT(("__MV__  msg queue is empty.\n"));
		return;
	} else if (!hba_msg_queue_empty() &&
		MSG_QUEUE_IDLE == queue_state_get()) {
	    	MV_DPRINT(("__MV__  msg queue isn't empty.\n"));
		mv_proc_queue();
	}
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,20)
#ifndef __VMKLNX__
static DECLARE_WORK(mv_wq, mv_wq_handler,NULL);
#else
static DECLARE_WORK(mv_wq, mv_wq_handler);
#endif
#else
static DECLARE_WORK(mv_wq, mv_wq_handler);
#endif

#endif

static void hba_msg_queue_init(void)
{
	int i;

	memset(&mv_msg_queue, 0, sizeof(sizeof(struct mv_hba_msg_queue)));
	spin_lock_init(&mv_msg_queue.lock);

	/* as we're in init, there should be no need to hold the spinlock*/
	MV_LIST_HEAD_INIT(&(mv_msg_queue.free));
	MV_LIST_HEAD_INIT(&(mv_msg_queue.tasks));

	for (i = 0; i < MSG_QUEUE_DEPTH; i++) {
		List_AddTail(&mv_msg_queue.msgs[i].msg_list,
			      &mv_msg_queue.free);
	}

}


void hba_house_keeper_init(void)
{
	hba_msg_queue_init();

	queue_state_set(MSG_QUEUE_NO_START);
#ifndef SUPPORT_WORKQUEUE
#if LINUX_KERNEL_VERSION > KERNEL_VERSION(2,6,0)
	house_keeper_task = kthread_create(hba_house_keeper, NULL, "399B4F5");
		MV_DPRINT((  "hba_house_keeper_init: house_keeper_task->%p\n", house_keeper_task));
	if (IS_ERR(house_keeper_task)) {
		MV_DPRINT((  "Error creating kthread, out of memory?\n"));
		house_keeper_task = NULL;
	}
#else
	marvell_hp_thread_id = kernel_thread((int (*)(void *))hba_house_keeper, NULL, 0);
#endif
#endif
}

void hba_house_keeper_run(void)
{
	queue_state_set(MSG_QUEUE_IDLE);
}

void hba_house_keeper_exit(void)
{
	queue_state_set(MSG_QUEUE_NO_START);
#if !defined(SUPPORT_WORKQUEUE) && (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,0))
	if (house_keeper_task)
		kthread_stop(house_keeper_task);
	house_keeper_task = NULL;
	return;
#endif

#if defined(SUPPORT_WORKQUEUE)
	flush_scheduled_work();
	return ;
#endif
#ifdef  MV_VMK_ESX35
	shutdown = 1;
	wake_up(&wait_queue);
	wait_for_completion(&marvell_hp_completion);
	kill_proc(marvell_hp_thread_id, SIGKILL, 0);
#endif
}


void hba_msg_insert(void *data, unsigned int msg, unsigned int param)
{
	struct mv_hba_msg *pmsg;
	unsigned long flags;

	MV_DPRINT(( "__MV__ msg insert  %d.\n", msg));
	spin_lock_irqsave(&mv_msg_queue.lock, flags);
	if (List_Empty(&mv_msg_queue.free)) {
		/* should wreck some havoc ...*/
		MV_DPRINT(("-- MV -- Message queue is full.\n"));
		need_rescan = MV_TRUE;
		rescan_hba = data;
		spin_unlock_irqrestore(&mv_msg_queue.lock, flags);
		return;
	}

	MV_DPRINT((   "__MV__ Message queue is not full.\n"));
	pmsg = LIST_ENTRY(mv_msg_queue.free.next, struct mv_hba_msg, msg_list);
	spin_unlock_irqrestore(&mv_msg_queue.lock, flags);

	pmsg->data = data;
	pmsg->msg  = msg;

	switch (msg) {
	case EVENT_DEVICE_REMOVAL:
	case EVENT_DEVICE_ARRIVAL:
		pmsg->param = param;
		break;
	default:
		pmsg->param = param;
		/*(NULL==param)?0:*((unsigned int*) param);*/
		break;
	}

	spin_lock_irqsave(&mv_msg_queue.lock, flags);
	List_MoveTail(&pmsg->msg_list, &mv_msg_queue.tasks);
	spin_unlock_irqrestore(&mv_msg_queue.lock, flags);

#ifdef SUPPORT_WORKQUEUE
	schedule_work(&mv_wq);
#else
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,0)
	if (house_keeper_task)
		wake_up_process(house_keeper_task);
#else
	wake_up(&wait_queue);
#endif
#endif
}

#ifdef SUPPORT_TIMER

MV_U16 Timer_GetRequestCount(MV_U16 maxIo)
{
	MV_U16 reqCount;

	/* when not in hibernation mode, allocate twice as many timers as # of
	  * devices because hot plug now requires a timer also for each device
	  */
	if (maxIo==1)
		reqCount = MAX_DEVICE_SUPPORTED_PERFORMANCE; /* no smart timer */
	else
		reqCount = (MAX_DEVICE_SUPPORTED_PERFORMANCE + 1) * 2;
#if defined(SUPPORT_CHIP_TIMEOUT)
	reqCount+=2;
#endif
	return reqCount;
}

MV_U32 Timer_GetResourceQuota(MV_U16 maxIo)
{
	MV_U32 sz;
	MV_U16 reqCount;

	reqCount = Timer_GetRequestCount(maxIo);
	/* Memory for timer tag pool */
	sz = ROUNDING((sizeof(MV_U16) * reqCount), 8);
	/* Memory for timer request array */
	sz += ROUNDING((sizeof(PTimer_Request) * reqCount), 8);
	/* Memory for timer request */
	sz += ROUNDING((sizeof(Timer_Request) * reqCount), 8);
	return sz;
}

void Timer_Initialize(
	IN  MV_PVOID This,
	IN MV_PU8 pool,
	IN MV_U16 max_io
	)
{
	PHBA_Extension pHBA = (PHBA_Extension)This;
	PTimer_Module	pTimer=(PTimer_Module)&pHBA->TimerModule;
	MV_PTR_INTEGER temp = (MV_PTR_INTEGER)pool;
	PTimer_Request pTimerReq;
	MV_U16 i, reqCount;

	ossw_init_timer(&pHBA->desc->hba_desc->hba_timer);

	reqCount = Timer_GetRequestCount(max_io);
	pTimer->Timer_Request_Number = reqCount;
	MV_DPRINT(("Timer_Request_Number = %d.\n", pTimer->Timer_Request_Number));
	/* allocate memory for timer request tag pool */
	pTimer->Tag_Pool.Stack = (MV_PU16)temp;
	pTimer->Tag_Pool.Size = reqCount;
	temp += sizeof(MV_U16) * reqCount;
	Tag_Init( &pTimer->Tag_Pool, reqCount );

	U64_ZERO_VALUE(pTimer->Time_Stamp);
	MV_ASSERT( sizeof(Timer_Request)==ROUNDING(sizeof(Timer_Request),8) );
	/* allocate memory for timer request array */
	pTimer->Running_Requests = (PTimer_Request *)temp;
	temp += sizeof(PTimer_Request) * reqCount;
	for (i = 0; i < reqCount; i++) {
		pTimerReq = (PTimer_Request)temp;
		U64_ZERO_VALUE(pTimerReq->Time_Stamp);
		pTimer->Running_Requests[i] = pTimerReq;
		temp += sizeof( Timer_Request );
	}
}

void Timer_Stop(MV_PVOID This)
{
	PHBA_Extension pHBA = (PHBA_Extension)This;
	ossw_del_timer(&pHBA->desc->hba_desc->hba_timer);
}


#ifdef SUPPORT_SMALL_TIMER
MV_U16 Timer_AddSmallRequest(
	IN MV_PVOID extension,
	IN MV_U32 time_unit,
	IN MV_VOID (*routine) (MV_PVOID, MV_PVOID),
	IN MV_PVOID context1,
	IN MV_PVOID context2
	)
{
	PHBA_Extension pHBA = (PHBA_Extension)HBA_GetModuleExtension(extension, MODULE_HBA);
	PTimer_Module pTimer = &pHBA->TimerModule;
	PTimer_Request pTimerReq;
	MV_U16 index;

	if (!Tag_IsEmpty( &pTimer->Tag_Pool )) {
		index = Tag_GetOne( &pTimer->Tag_Pool );
		pTimerReq = pTimer->Running_Requests[index];

		pTimerReq->Valid = MV_TRUE;
		pTimerReq->Context1 = context1;
		pTimerReq->Context2 = context2;
		pTimerReq->Routine = routine;
		pTimerReq->Time_Stamp = U64_ADD_U32(pTimer->Time_Stamp,
			time_unit * TIMER_INTERVAL_SMALL_UNIT );

		return index;
	}

	/* shouldn't happen - we should always allocate enough timer slots for all devices */
	MV_DASSERT( MV_FALSE );
	return NO_CURRENT_TIMER;
}
#endif

MV_U16 Timer_AddRequest(
	IN MV_PVOID extension,
	IN MV_U32 time_unit,
	IN MV_VOID (*routine) (MV_PVOID, MV_PVOID),
	IN MV_PVOID context1,
	IN MV_PVOID context2
	)
{
	PHBA_Extension pHBA = (PHBA_Extension)HBA_GetModuleExtension(extension, MODULE_HBA);
	PTimer_Module pTimer = &pHBA->TimerModule;
	PTimer_Request pTimerReq;
	MV_U16 index;

	if (!Tag_IsEmpty( &pTimer->Tag_Pool)) {
		index = (MV_U16)Tag_GetOne( &pTimer->Tag_Pool );
		pTimerReq = pTimer->Running_Requests[index];

		pTimerReq->Valid = MV_TRUE;
		pTimerReq->Context1 = context1;
		pTimerReq->Context2 = context2;
		pTimerReq->Routine = routine;
		pTimerReq->Time_Stamp = U64_ADD_U32(pTimer->Time_Stamp,
			time_unit * TIMER_INTERVAL_LARGE_UNIT );
		return index;
	}

	/* shouldn't happen - we should always allocate enough timer slots for all devices */
	MV_DPRINT(("Timer_AddRequest: no enough timer slots \n"));
	MV_DASSERT( MV_FALSE );
	return NO_CURRENT_TIMER;
}

void Timer_CheckRequest(
	IN MV_PVOID extension
	)
{
	PHBA_Extension pHBA = (PHBA_Extension)HBA_GetModuleExtension(extension, MODULE_HBA);
	PTimer_Module pTimer = &pHBA->TimerModule;
	PTimer_Request pTimerReq;
	MV_PVOID core = NULL;
	MV_U16 i; 
#ifndef SUPPORT_TASKLET
		MV_ULONG flags;
		spin_lock_irqsave(&pHBA->desc->hba_desc->global_lock, flags);
#else
		spin_lock_bh(&pHBA->desc->hba_desc->global_lock);
#endif
		pTimer->Time_Stamp = U64_ADD_U32(pTimer->Time_Stamp, TIMER_INTERVAL_OS);

		for (i=0; i<pTimer->Timer_Request_Number; i++) {
			pTimerReq = pTimer->Running_Requests[i];
			if (pTimerReq && pTimerReq->Valid && (pTimerReq->Time_Stamp.value <= pTimer->Time_Stamp.value)) {
				MV_DASSERT( pTimerReq->Routine != NULL );
				pTimerReq->Routine( pTimerReq->Context1, pTimerReq->Context2 );
				if (pTimerReq->Valid) {
					pTimerReq->Valid = MV_FALSE;
					Tag_ReleaseOne( &pTimer->Tag_Pool, i );
				}
			}
		}

#ifdef CORE_NO_RECURSIVE_CALL
		core = (MV_PVOID)HBA_GetModuleExtension(extension, MODULE_CORE);
		core_push_queues(core);
#endif

		mod_timer(&pHBA->desc->hba_desc->hba_timer, jiffies + msecs_to_jiffies(TIMER_INTERVAL_OS));

#ifndef SUPPORT_TASKLET
		spin_unlock_irqrestore(&pHBA->desc->hba_desc->global_lock, flags);
#else
		spin_unlock_bh(&pHBA->desc->hba_desc->global_lock);
#endif

}

void Timer_CancelRequest(
	IN MV_PVOID extension,
	IN MV_U16 request_index
	)
{
	PHBA_Extension pHBA = (PHBA_Extension)HBA_GetModuleExtension(extension, MODULE_HBA);
	PTimer_Module pTimer = &pHBA->TimerModule;
	PTimer_Request pTimerReq;

	if (request_index < pTimer->Timer_Request_Number) {
		pTimerReq = pTimer->Running_Requests[request_index];

		if(pTimerReq->Valid && (pTimerReq->Time_Stamp.value >=  pTimer->Time_Stamp.value)) {
			pTimerReq->Valid = MV_FALSE;
			Tag_ReleaseOne( &pTimer->Tag_Pool, (MV_U16)request_index );
		}
	}
}
#endif

