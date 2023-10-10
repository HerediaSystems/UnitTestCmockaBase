

#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

typedef struct HAL_GPIO_OBJ HAL_GPIO_OBJ;

struct HAL_GPIO_OBJ
{
    uint8_t pin_num;
};


typedef enum
{
    HAL_GPIO_PORT_DEFAULT
} HAL_GPIO_PORT;

typedef enum
{
    HAL_GPIO_MODE_IN,
    HAL_GPIO_MODE_OUT,
    HAL_GPIO_MODE_AF,
    HAL_GPIO_MODE_ANALOG
} HAL_GPIO_MODE;

typedef enum
{
    HAL_GPIO_LVL_HIGH,
    HAL_GPIO_LVL_LOW
} HAL_GPIO_LVL;

void HAL_GPIO_init(HAL_GPIO_OBJ *obj,HAL_GPIO_PORT port,uint8_t pin_num, HAL_GPIO_MODE mode);
void HAL_GPIO_toggle(HAL_GPIO_OBJ *obj);
HAL_GPIO_LVL HAL_GPIO_get(HAL_GPIO_OBJ *obj);
void HAL_GPIO_set(HAL_GPIO_OBJ *obj,HAL_GPIO_LVL lvl);

#ifdef __cplusplus
}
#endif



#endif
