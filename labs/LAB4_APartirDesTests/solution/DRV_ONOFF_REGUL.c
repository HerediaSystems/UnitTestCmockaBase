#include "DRV_ONOFF_REGUL.h"
#include "SYS_assert.h"

#include <stdlib.h>

void DRV_ONOFF_REGUL_init(DRV_ONOFF_REGUL_OBJ *obj,uint32_t hysteresis, void (*commande)(DRV_ONOFF_REGUL_OBJ *obj,bool on))
{
    assert(obj != NULL);
    assert(commande != NULL);
    assert(hysteresis >= 1);
    assert(hysteresis <= 20);

    obj->hysteresis = hysteresis;
    obj->target = 0;
    obj->commande = commande;
}

void DRV_ONOFF_REGUL_setTarget(DRV_ONOFF_REGUL_OBJ *obj,int32_t target)
{
    assert(obj != NULL);
    assert(target >= -50);
    assert(target <= 100);

    obj->target = target;
}

void DRV_ONOFF_REGUL_updateTemperature(DRV_ONOFF_REGUL_OBJ *obj,int32_t temperature)
{
    assert(obj != NULL);
    assert(temperature >= -100);
    assert(temperature <= 150);

    if(temperature > (obj->target + obj->hysteresis))
    {
        obj->commande(obj,false);
    }

    if(temperature < (obj->target - obj->hysteresis))
    {
        obj->commande(obj,true);
    }
}