#ifndef __MV_COM_TAG_H__
#define __MV_COM_TAG_H__

#include "com_define.h"

typedef struct _Tag_Stack Tag_Stack, *PTag_Stack;

#define FILO_TAG 0x00
#define FIFO_TAG 0x01

/* if TagStackType!=FIFO_TAG, use FILO, */
/* if TagStackType==FIFO_TAG, use FIFO, PtrOut is the next tag to get */
/*  and Top is the number of available tags in the stack */
/* when use FIFO, get tag from PtrOut and free tag to (PtrOut+Top)%Size */
struct _Tag_Stack
{
	MV_PU16  Stack;
	MV_U16   Size;
	MV_U16   Top;
	MV_U16   PtrOut;
	MV_U8    TagStackType;
#ifndef _OS_BIOS
	MV_U8    Reserved[1];	
#endif
};

MV_VOID Tag_Init(PTag_Stack pTagStack, MV_U16 size);
#if !defined(MV_ROC_IOP_TUNED)
MV_VOID Tag_Init_FIFO( PTag_Stack pTagStack, MV_U16 size );
MV_U16 Tag_GetOne(PTag_Stack pTagStack) ;
MV_VOID Tag_ReleaseOne(PTag_Stack pTagStack, MV_U16 tag);
MV_BOOLEAN Tag_IsEmpty(PTag_Stack pTagStack);
#else
#define Tag_Init_FIFO( pTagStack, size )			\
do{													\
	Tag_Init((pTagStack), (size));					\
	(pTagStack)->TagStackType = FIFO_TAG; 			\
}while(0)

#define Tag_GetOne(pTagStack_)						\
({ register PTag_Stack pTagStack = (pTagStack_);	\
	MV_U16 nTag;									\
	MV_U16 i = pTagStack->Top&0x7FFF;				\
	pTagStack->Top&= 0x8000;						\
	if (i>0) {										\
		i--;										\
	} else {										\
		i = (pTagStack->Size-1);					\
		pTagStack->Top^= 0x8000;					\
	}												\
	pTagStack->Top|= i;								\
	nTag = pTagStack->Stack[i];						\
	(nTag);											\
})

#define Tag_ReleaseOne( pTagStack_, tag)			\
do{ register PTag_Stack pTagStack = (pTagStack_);	\
	if(pTagStack->TagStackType==FIFO_TAG){			\
		MV_U16 i = pTagStack->PtrOut&0x7FFF;		\
		pTagStack->PtrOut&= 0x8000;					\
		if (i>0) {									\
			i--;									\
		} else {									\
			i = (pTagStack->Size-1);				\
			pTagStack->PtrOut^= 0x8000;				\
		}											\
		pTagStack->PtrOut|= i;						\
		pTagStack->Stack[i] = tag;					\
	} else {										\
		pTagStack->Stack[pTagStack->Top++] = tag;	\
	} 												\
}while(0)

#define Tag_IsEmpty(pTagStack)	((pTagStack)->PtrOut==(pTagStack)->Top)
#endif


#endif /*  __MV_COM_TAG_H__ */
