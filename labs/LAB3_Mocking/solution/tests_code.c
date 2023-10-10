#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "DRV_LED.h"

/* stubs */
uint64_t __wrap_SYS_TIMESTAMP_get(void)
{
    return (uint64_t) mock();
}

void __wrap_HAL_GPIO_set(HAL_GPIO_OBJ *obj,HAL_GPIO_LVL lvl)
{
    check_expected(obj);
    check_expected(lvl);
}

void __wrap_HAL_GPIO_toggle(HAL_GPIO_OBJ *obj)
{
    check_expected(obj);
}
/* ---------------- */


/* créer de fonctions de tests sur le principe de celle-ci*/
#define FAST_PERIOD 50
#define SLOW_PERIOD 500

static void test_task_blink_fast_toggle(void **state) 
{ 
    DRV_LED_OBJ obj;
    HAL_GPIO_OBJ gpio;
    
    /* on initialise l'objet LED pour le test*/
    obj.gpio = &gpio; /* on lui fourni une fausse instance de GPIO*/
    obj.nextEventMs = 2000; /* on place l'objet LED dans l'état où le prochaine événement sera à la date 2000ms */
    obj.state = DRV_LED_STATE_BLINK_FAST; /* l'objet LED est dans le mode "BLINK_FAST" */

    will_return_always(__wrap_SYS_TIMESTAMP_get, (uint64_t)3000); /* on s'attend à ce que l'objet LED appel TIMESTAMP_get, le mock de celui-ci retournera 3000 ms*/
    expect_memory(__wrap_HAL_GPIO_toggle, obj, &gpio, sizeof(gpio)); /* la date du timestamp etant supérieur à la date de l'évenement, on s'attend à ce que l'objet LED demande de toggle la GPIO */
    DRV_LED_task(&obj); /* executer la fonction */
    assert_int_equal(obj.nextEventMs,3000 + FAST_PERIOD ); /* verifier que la nextEventMs a bien été mis à jour avec la bonne valeur */
}

static void test_task_blink_fast_wait(void **state) 
{ 
    DRV_LED_OBJ obj;
    HAL_GPIO_OBJ gpio;
    
    /* on initialise l'objet LED pour le test*/
    obj.gpio = &gpio; /* on lui fourni une fausse instance de GPIO*/
    obj.nextEventMs = 4000; /* on place l'objet LED dans l'état où le prochaine événement sera à la date 4000ms */
    obj.state = DRV_LED_STATE_BLINK_FAST; /* l'objet LED est dans le mode "BLINK_FAST" */

    will_return_always(__wrap_SYS_TIMESTAMP_get, (uint64_t)3000); /* on s'attend à ce que l'objet LED appel TIMESTAMP_get, le mock de celui-ci retournera 3000 ms*/
    /* on n'attend pas d'autre appel de fonction */
    DRV_LED_task(&obj); /* executer la fonction */
    assert_int_equal(obj.nextEventMs,4000 ); /* verifier que la nextEventMs ,n'a pas été modifié */
}

static void test_set_OFFtoON(void **state) 
{ 
    DRV_LED_OBJ obj;
    HAL_GPIO_OBJ gpio;
    
    /* on initialise l'objet LED pour le test*/
    obj.gpio = &gpio; /* on lui fourni une fausse instance de GPIO*/
    obj.nextEventMs = 0; /* on initialise la prochaine évenement à 0 */
    obj.state = DRV_LED_STATE_OFF; /* l'objet LED est dans le mode "OFF" */

    expect_memory(__wrap_HAL_GPIO_set, obj, &gpio, sizeof(gpio)); /* on s'attend a ce que la GPIO soit piloté */
    expect_value(__wrap_HAL_GPIO_set, lvl, HAL_GPIO_LVL_HIGH);  /* avec une valeur "niveau haut" */
    DRV_LED_set(&obj,DRV_LED_STATE_ON); /* executer la fonction pour passer le mode à ON */
    assert_int_equal(obj.state,DRV_LED_STATE_ON); /* verifier que le mode a bien pris la bonne valeur */
}
    
static void test_set_OFFtoOFF(void **state) 
{ 
    DRV_LED_OBJ obj;
    HAL_GPIO_OBJ gpio;
    
    /* on initialise l'objet LED pour le test*/
    obj.gpio = &gpio; /* on lui fourni une fausse instance de GPIO*/
    obj.nextEventMs = 0; /* on initialise la prochaine évenement à 0 */
    obj.state = DRV_LED_STATE_OFF; /* l'objet LED est dans le mode "OFF" */

    
    expect_memory(__wrap_HAL_GPIO_set, obj, &gpio, sizeof(gpio)); /* on s'attend a ce que la GPIO soit piloté */
    expect_value(__wrap_HAL_GPIO_set, lvl, HAL_GPIO_LVL_LOW);  /* avec une valeur "niveau bas" */
    DRV_LED_set(&obj,DRV_LED_STATE_OFF); /* executer la fonction pour passer le mode à OFF */
    assert_int_equal(obj.state,DRV_LED_STATE_OFF); /* verifier que le mode a bien pris la bonne valeur */
}

static void test_set_OFFtoBLINK_FAST(void **state) 
{ 
    DRV_LED_OBJ obj;
    HAL_GPIO_OBJ gpio;
    
    /* on initialise l'objet LED pour le test*/
    obj.gpio = &gpio; /* on lui fourni une fausse instance de GPIO*/
    obj.nextEventMs = 0; /* on initialise la prochaine évenement à 0 */
    obj.state = DRV_LED_STATE_OFF; /* l'objet LED est dans le mode "OFF" */

    will_return_always(__wrap_SYS_TIMESTAMP_get, (uint64_t)3000); /* on s'attend à ce que l'objet LED appel TIMESTAMP_get, le mock de celui-ci retournera 3000 ms*/
    expect_memory(__wrap_HAL_GPIO_set, obj, &gpio, sizeof(gpio)); /* on s'attend a ce que la GPIO soit piloté */
    expect_value(__wrap_HAL_GPIO_set, lvl, HAL_GPIO_LVL_LOW);  /* avec une valeur "niveau bas" */
    DRV_LED_set(&obj,DRV_LED_STATE_BLINK_FAST); /* executer la fonction pour passer le mode à OFF */
    assert_int_equal(obj.state,DRV_LED_STATE_BLINK_FAST); /* verifier que le mode a bien pris la bonne valeur */
    assert_int_equal(obj.nextEventMs,3000 + FAST_PERIOD ); /* verifier que la nextEventMs a bien été mis à jour avec la bonne valeur */
}


int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_task_blink_fast_toggle),
        cmocka_unit_test(test_task_blink_fast_wait),
        cmocka_unit_test(test_set_OFFtoON),
        cmocka_unit_test(test_set_OFFtoOFF),
        cmocka_unit_test(test_set_OFFtoBLINK_FAST),
        
        /* ajouter des tests a la liste */
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
