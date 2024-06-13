/*
 *
 * File: DRV_ONOFF_REGUL.c
 * Author: Maxime HEREDIA-HIDALGO
 * Copyright (c) 2024  HerediaSystems : https://www.heredia-systems.com/
 *
 */

#include "DRV_ONOFF_REGUL.h"
#include "SYS_assert.h"

#include <stdlib.h>

void DRV_ONOFF_REGUL_init(DRV_ONOFF_REGUL_OBJ *obj, uint32_t hysteresis, void (*commande)(DRV_ONOFF_REGUL_OBJ *obj, bool on))
{
}

void DRV_ONOFF_REGUL_setTarget(DRV_ONOFF_REGUL_OBJ *obj, int32_t target)
{
    /* à compléter */
}

void DRV_ONOFF_REGUL_updateTemperature(DRV_ONOFF_REGUL_OBJ *obj, int32_t temperature)
{
    /* à compléter */
}