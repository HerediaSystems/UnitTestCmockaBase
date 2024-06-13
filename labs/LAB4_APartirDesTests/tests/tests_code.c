/*
 *
 * File: tests_code.c
 * Author: Maxime HEREDIA-HIDALGO
 * Copyright (c) 2024  HerediaSystems : https://www.heredia-systems.com/
 *
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "DRV_ONOFF_REGUL.h"

static void callback_command(DRV_ONOFF_REGUL_OBJ *obj, bool on)
{
    check_expected(obj);
    check_expected(on);
}

static void test_init_usecase(void **state)
{
    DRV_ONOFF_REGUL_OBJ obj;

    DRV_ONOFF_REGUL_init(&obj, 5, callback_command);
    assert_int_equal(obj.target, 0);
    assert_int_equal(obj.hysteresis, 5);
    assert_ptr_equal(obj.commande, callback_command);
}

static void test_init_edge(void **state)
{
    DRV_ONOFF_REGUL_OBJ obj;

    DRV_ONOFF_REGUL_init(&obj, 1, callback_command);
    assert_int_equal(obj.target, 0);
    assert_int_equal(obj.hysteresis, 1);
    assert_ptr_equal(obj.commande, callback_command);

    DRV_ONOFF_REGUL_init(&obj, 20, callback_command);
    assert_int_equal(obj.target, 0);
    assert_int_equal(obj.hysteresis, 20);
    assert_ptr_equal(obj.commande, callback_command);
}

static void test_init_assert(void **state)
{
    DRV_ONOFF_REGUL_OBJ obj;

    expect_assert_failure(DRV_ONOFF_REGUL_init(NULL, 5, callback_command));
    expect_assert_failure(DRV_ONOFF_REGUL_init(&obj, 0, callback_command));
    expect_assert_failure(DRV_ONOFF_REGUL_init(&obj, 30, callback_command));
    expect_assert_failure(DRV_ONOFF_REGUL_init(&obj, 5, NULL));
}

static void test_setTarget_usecase(void **state)
{
    DRV_ONOFF_REGUL_OBJ obj;

    obj.commande = callback_command;
    obj.hysteresis = 1;
    obj.target = 0;

    DRV_ONOFF_REGUL_setTarget(&obj, 20);
    assert_int_equal(obj.target, 20);
    assert_int_equal(obj.hysteresis, 1);
    assert_ptr_equal(obj.commande, callback_command);
}

static void test_setTarget_edge(void **state)
{
    DRV_ONOFF_REGUL_OBJ obj;

    obj.commande = callback_command;
    obj.hysteresis = 1;
    obj.target = 0;

    DRV_ONOFF_REGUL_setTarget(&obj, -50);
    assert_int_equal(obj.target, -50);
    assert_int_equal(obj.hysteresis, 1);
    assert_ptr_equal(obj.commande, callback_command);

    obj.commande = callback_command;
    obj.hysteresis = 1;
    obj.target = 0;

    DRV_ONOFF_REGUL_setTarget(&obj, 100);
    assert_int_equal(obj.target, 100);
    assert_int_equal(obj.hysteresis, 1);
    assert_ptr_equal(obj.commande, callback_command);
}

static void test_setTarget_assert(void **state)
{
    DRV_ONOFF_REGUL_OBJ obj;

    expect_assert_failure(DRV_ONOFF_REGUL_setTarget(NULL, 20));
    expect_assert_failure(DRV_ONOFF_REGUL_setTarget(&obj, 130));
    expect_assert_failure(DRV_ONOFF_REGUL_setTarget(&obj, -100));
}

static void test_updateTemperature_usecase(void **state)
{
    DRV_ONOFF_REGUL_OBJ obj;

    obj.commande = callback_command;
    obj.hysteresis = 5;
    obj.target = 20;

    DRV_ONOFF_REGUL_updateTemperature(&obj, 20);

    expect_memory(callback_command, obj, &obj, sizeof(obj));
    expect_value(callback_command, on, true);
    DRV_ONOFF_REGUL_updateTemperature(&obj, 10);

    expect_memory(callback_command, obj, &obj, sizeof(obj));
    expect_value(callback_command, on, false);
    DRV_ONOFF_REGUL_updateTemperature(&obj, 30);
}

static void test_updateTemperature_edge(void **state)
{
    DRV_ONOFF_REGUL_OBJ obj;

    obj.commande = callback_command;
    obj.hysteresis = 5;
    obj.target = 20;

    DRV_ONOFF_REGUL_updateTemperature(&obj, 15);
    DRV_ONOFF_REGUL_updateTemperature(&obj, 25);

    expect_memory(callback_command, obj, &obj, sizeof(obj));
    expect_value(callback_command, on, true);
    DRV_ONOFF_REGUL_updateTemperature(&obj, 14);

    expect_memory(callback_command, obj, &obj, sizeof(obj));
    expect_value(callback_command, on, false);
    DRV_ONOFF_REGUL_updateTemperature(&obj, 26);
}
static void test_updateTemperature_assert(void **state)
{
    DRV_ONOFF_REGUL_OBJ obj;

    obj.commande = callback_command;
    obj.hysteresis = 5;
    obj.target = 20;

    expect_assert_failure(DRV_ONOFF_REGUL_updateTemperature(NULL, 20));
    expect_assert_failure(DRV_ONOFF_REGUL_updateTemperature(&obj, -101));
    expect_assert_failure(DRV_ONOFF_REGUL_updateTemperature(&obj, 151));
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_init_usecase),
        cmocka_unit_test(test_init_edge),
        cmocka_unit_test(test_init_assert),

        cmocka_unit_test(test_setTarget_usecase),
        cmocka_unit_test(test_setTarget_edge),
        cmocka_unit_test(test_setTarget_assert),

        cmocka_unit_test(test_updateTemperature_usecase),
        cmocka_unit_test(test_updateTemperature_edge),
        cmocka_unit_test(test_updateTemperature_assert),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
