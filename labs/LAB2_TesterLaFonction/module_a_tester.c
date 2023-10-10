#include "module_a_tester.h"

int32_t MOD256(int32_t valeur)
{
    int32_t result;
    
    result = valeur & 0xFF;
    
    return result;
}