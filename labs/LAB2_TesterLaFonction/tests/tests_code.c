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

#include "module_a_tester.h"

/* créer de fonctions de tests sur le principe de celle-ci*/
static void test_zero(void **state)
{
    assert_int_equal(MOD256(0), 0);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_zero),
        /* ajouter des tests a la liste */
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
