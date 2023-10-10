

#ifndef __SYS_TIMESTAMP_H
#define __SYS_TIMESTAMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

#define TIMESTAMP_MAX_VALUE 0xFFFFFFFF

#define HAL_TMR_ID uint32_t //mock du type

void SYS_TIMESTAMP_init(HAL_TMR_ID timer_ID);
uint64_t SYS_TIMESTAMP_get();


#ifdef __cplusplus
}
#endif



#endif
