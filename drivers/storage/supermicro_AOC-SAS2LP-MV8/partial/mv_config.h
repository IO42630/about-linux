#if !defined(MV_CONFIGURATION_H)
#define MV_CONFIGURATION_H
#ifdef PRODUCTNAME_ODIN
#include "mv_config_odin.h"
#elif defined(PRODUCTNAME_VANIR) || defined(PRODUCTNAME_VANIRLITES)
#include "mv_config_vanir.h"
#elif defined(SIMULATOR)
#include "mv_simu.h"
#elif defined(PRODUCTNAME_THOR)
#include "mv_config_thor.h"
#elif defined(PRODUCTNAME_MAGNI)
#include "mv_config_magni.h"
#endif /*PRODUCTNAME_ODIN , PRODUCTNAME_THOR*/
#endif /* MV_CONFIGURATION_H */
