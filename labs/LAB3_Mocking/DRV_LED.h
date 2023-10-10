

#ifndef __DRV_LED_H
#define __DRV_LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "HAL/GPIO/HAL_GPIO.h"
#include "stdint.h"

typedef enum
{
    DRV_LED_STATE_OFF,
    DRV_LED_STATE_ON,
    DRV_LED_STATE_BLINK_SLOW,
    DRV_LED_STATE_BLINK_FAST,
} DRV_LED_STATE;

typedef struct DRV_LED_OBJ DRV_LED_OBJ;

struct DRV_LED_OBJ
{
	HAL_GPIO_OBJ *gpio;
    DRV_LED_STATE state;
    uint64_t nextEventMs;
};

void DRV_LED_init(DRV_LED_OBJ *obj,HAL_GPIO_OBJ *gpio);
void DRV_LED_set(DRV_LED_OBJ *obj,DRV_LED_STATE state);
void DRV_LED_task(DRV_LED_OBJ *obj);

#ifdef __cplusplus
}
#endif



#endif
