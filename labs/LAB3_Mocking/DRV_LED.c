
#include "SYS/Timestamp/SYS_Timestamp.h"
#include "DRV_LED.h"

#define FAST_PERIOD 50
#define SLOW_PERIOD 500

static void stateTransition(DRV_LED_OBJ *obj,DRV_LED_STATE state)
{
    switch(state)
    {
        case DRV_LED_STATE_OFF:
            obj->state = DRV_LED_STATE_OFF;
            HAL_GPIO_set(obj->gpio,HAL_GPIO_LVL_LOW);
        break;
        case DRV_LED_STATE_ON:
            obj->state = DRV_LED_STATE_ON;
            HAL_GPIO_set(obj->gpio,HAL_GPIO_LVL_HIGH);
        break;
        case DRV_LED_STATE_BLINK_FAST:
            obj->state = DRV_LED_STATE_BLINK_FAST;
            HAL_GPIO_set(obj->gpio,HAL_GPIO_LVL_LOW);
            obj->nextEventMs = SYS_TIMESTAMP_get()+FAST_PERIOD;
        break;
        case DRV_LED_STATE_BLINK_SLOW:
            obj->state = DRV_LED_STATE_BLINK_SLOW;
            HAL_GPIO_set(obj->gpio,HAL_GPIO_LVL_LOW);
            obj->nextEventMs = SYS_TIMESTAMP_get()+SLOW_PERIOD;
        break;
        default:
            obj->state = DRV_LED_STATE_OFF;
            HAL_GPIO_set(obj->gpio,HAL_GPIO_LVL_LOW);
        break;
    }
}

void DRV_LED_init(DRV_LED_OBJ *obj,HAL_GPIO_OBJ *gpio)
{
    obj->gpio = gpio;
    obj->state = DRV_LED_STATE_OFF;
}

void DRV_LED_set(DRV_LED_OBJ *obj,DRV_LED_STATE state)
{
    stateTransition(obj,state);
}

void DRV_LED_task(DRV_LED_OBJ *obj)
{
    switch(obj->state)
    {
        case DRV_LED_STATE_OFF:
        break;
        case DRV_LED_STATE_ON:
        break;
        case DRV_LED_STATE_BLINK_FAST:
            if(SYS_TIMESTAMP_get() >= obj->nextEventMs)
            {
                HAL_GPIO_toggle(obj->gpio);
                obj->nextEventMs = SYS_TIMESTAMP_get()+FAST_PERIOD;
            } 
        break;
        case DRV_LED_STATE_BLINK_SLOW:
            if(SYS_TIMESTAMP_get() >= obj->nextEventMs)
            {
                HAL_GPIO_toggle(obj->gpio);
                obj->nextEventMs = SYS_TIMESTAMP_get()+SLOW_PERIOD;
            }
        break;
        default:
        break;
    }
}

