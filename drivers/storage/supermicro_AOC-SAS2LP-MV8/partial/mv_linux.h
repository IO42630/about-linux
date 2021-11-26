/*This file defined macro only used by Linux driver.*/
#ifndef __MV_LINUX_H__
#define __MV_LINUX_H__

#ifdef MV_DEBUG
#define SUPPORT_CHANGE_DEBUG_MODE	1
#endif
#define SUPPORT_CHANGE_CAN_QUEUE		1

#ifndef MV_VMK_ESX35
#define SUPPORT_WORKQUEUE       	1
#ifndef __VMKLNX__
#define MV_BLK_IOCTL           	 		1
#define SUPPORT_TASKLET		1
#endif
#define USE_REQ_POOL  			1
#endif

#define CACHE_NAME_LEN 			32

//#define API_GET_ENC_ID

/*dynamic memory alloc for command table and sg entry*/
#ifndef MV_VMK_ESX35
#define PCI_POOL_SUPPORT
#endif
/*
 * define USE_NEW_SGTABLE to use the new SG format as defined in
 * "General SG Format" document.
 */
#ifdef USE_NEW_SGTABLE
#define USE_NEW_SGVP
#endif /* USE_NEW_SGTABLE */

/*Max ID report to OS: HD+Enclosure+PM+virtual device*/
#define MV_MAX_ID                                      \
        (MV_MAX_TARGET_NUMBER + MAX_EXPANDER_SUPPORTED + \
         MAX_PM_SUPPORTED + 1)/*reserved 1 ID for virtual device ID*/			

#endif /* __MV_LINUX_H__ */

