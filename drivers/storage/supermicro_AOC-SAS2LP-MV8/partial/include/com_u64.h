#ifndef _U64_H__
#define _U64_H__
#define U64_ASSIGN_SAFE(v1, v2)	\
do{	int i; \
	for (i=0; i<sizeof((v1)); i++)	\
		((char*)&v1)[i] = ((char*)(v2))[i];	\
}while(0)
#if defined (MV_ROC_IOP_TUNED) ||defined(_OS_UKRN)
#define U64_LIB_TYPE		0
#else
#define U64_LIB_TYPE		2
#endif
#if U64_LIB_TYPE==0||U64_LIB_TYPE==1
#define U64_ADD_U32(v1, v2)											\
({                                                                      \
	register MV_U64 a;              					\
	a.value=(v1).value+(v2); a;                                          \
})                                                                      
#define U64_SUBTRACT_U32(v1, v2)                        \
({                                                                      \
	register MV_U64 a;              					\
	a.value=(v1).value-(v2); a;                                                      \
})                                                                      
#define U64_ADD_U64(v1, v2)                                \
({                                                                      \
	register MV_U64 a;              					\
	a.value=(v1).value+(v2).value; a;                                                      \
})                                                                      
#define U64_SUBTRACT_U64(v1, v2) 	\
({	\
	register MV_U64 a;              					\
	a.value=(v1).value-(v2).value; a;                                                      \
})
#define U64_COMPARE_U64_(v1, v2) 	\
({	\
	register int r;	\
	if ((v1)==(v2)) r = 0; else if((v1)>(v2)) r = 1; else r = -1; r;                                                   \
})

#define U64_COMPARE_U64(v1, v2)     U64_COMPARE_U64_((v1).value, (v2).value)
#define U64_COMPARE_U32(v1, v2)		U64_COMPARE_U64_((v1).value, (v2))
#define U64_SET_VALUE(v64, v32)		(v64).value = (_MV_U64)(v32)
#define U64_SET_MAX_VALUE(v64)		(v64).value = 0xFFFFFFFFFFFFFFFFLL
#endif
#if U64_LIB_TYPE==0
#define U64_MULTIPLY_U32(v1, v2)                         \
({                                                                      \
	register MV_U64 a;              					\
	a.value=(v1).value*(v2); a;                                                      \
})                                                                      
#define U64_DIVIDE_U64(v1, v2)                             				\
({                                                                      \
	register MV_U32 a;              					\
	a=(v1).value/(v2).value; a;                                                      \
})                                                                      
#define U64_MOD_U32(v1, v2)		\
({                                                                      \
	register MV_U32 a;              					\
	a=(v1).value%(v2); a;                                                      \
})                                                                      
#define U64_DIVIDE_U32(v1, v2)                             				\
({                                                                      \
	register MV_U64 a;              					\
	a.value=(v1).value/(v2); a;                                                      \
})                                                                      
#elif U64_LIB_TYPE==1
MV_U64 U64_MULTIPLY_U32(MV_U64 v64, MV_U32 v32);
MV_U64 U64_DIVIDE_U32(MV_U64 v64, MV_U32 v32);
MV_U32 U64_MOD_U32(MV_U64 v64, MV_U32 v32);
MV_U32 U64_DIVIDE_U64(MV_U64 v1, MV_U64 v2);
#elif U64_LIB_TYPE==2
MV_U64 U64_ADD_U32(MV_U64 v64, MV_U32 v32);
MV_U64 U64_SUBTRACT_U32(MV_U64 v64, MV_U32 v32);
MV_U64 U64_MULTIPLY_U32(MV_U64 v64, MV_U32 v32);
MV_U64 U64_DIVIDE_U32(MV_U64 v64, MV_U32 v32);
MV_I32 U64_COMPARE_U32(MV_U64 v64, MV_U32 v32);
MV_U32 U64_MOD_U32(MV_U64 v64, MV_U32 v32);

MV_U64 U64_ADD_U64(MV_U64 v1, MV_U64 v2);
MV_U64 U64_SUBTRACT_U64(MV_U64 v1, MV_U64 v2);
MV_U32 U64_DIVIDE_U64(MV_U64 v1, MV_U64 v2);
MV_I32 U64_COMPARE_U64(MV_U64 v1, MV_U64 v2);

#ifndef _OS_BIOS
#define U64_SET_VALUE(v64, v32)	do { v64.value = v32; } while(0)
#else
#define U64_SET_VALUE(v64, v32)	do {v64.low = v32;v64.high=0;} while(0)
MV_U64 U64_SHIFT_LEFTN(MV_U64 v64, MV_U8 num);
MV_U64 U64_SHIFT_RIGHTN(MV_U64 v64, MV_U8 num);
#endif

#define U64_SET_MAX_VALUE(v64)	do { v64.parts.low = v64.parts.high = 0xFFFFFFFFL; } while(0);

#endif

#endif

