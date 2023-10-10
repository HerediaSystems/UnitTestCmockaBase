#ifndef __DRV_ONOFF_REGUL_H
#define __DRV_ONOFF_REGUL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"

typedef struct DRV_ONOFF_REGUL_OBJ DRV_ONOFF_REGUL_OBJ;
struct DRV_ONOFF_REGUL_OBJ
{
    int32_t target; /* température cible (entre -50 et +100) */
    
    /* Si la temperature dépasse la "target" de plus de l'hysteresis, la commande doit etre désactivé.
       Si elle passe en dessous de la "target" moins l'hysteresis, la commande doit etre activé */
    uint32_t hysteresis;  /* entre 1 et 20 */

    void (*commande)(DRV_ONOFF_REGUL_OBJ *obj,bool on); /* le callback de commande*/
};

void DRV_ONOFF_REGUL_init(DRV_ONOFF_REGUL_OBJ *obj,uint32_t hysteresis, void (*commande)(DRV_ONOFF_REGUL_OBJ *obj,bool on)); /* initialisation de l'objet : definir l'hysteresis , définir la fonction de commande, "target" et température mis à 0 */
void DRV_ONOFF_REGUL_setTarget(DRV_ONOFF_REGUL_OBJ *obj,int32_t target); /* modifier la valeur de la "target" */
void DRV_ONOFF_REGUL_updateTemperature(DRV_ONOFF_REGUL_OBJ *obj,int32_t temperature); /* mettre à jour la température (entre -100 et +150),  executer la régulation */

#ifdef __cplusplus
}
#endif



#endif
