#include "module_a_tester.h"

int32_t MOD256(int32_t valeur)
{
    int32_t result;

    if(valeur<0)
    {
        result = (-valeur) & 0xFF;
        result = -result;
    } 
    else
    {
        result = valeur & 0xFF;
    }
    
    return result;
}