/*
 *
 * File: module_a_tester.c
 * Author: Maxime HEREDIA-HIDALGO
 * Copyright (c) 2024  HerediaSystems : https://www.heredia-systems.com/
 *
 */

#include "module_a_tester.h"

int32_t MOD256(int32_t valeur)
{
    int32_t result;

    result = valeur & 0xFF;

    return result;
}