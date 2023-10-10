#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "module_a_tester.h"

static void test_zero(void **state) 
{ 
    assert_int_equal( MOD256(0) , 0 ); 
}

static void test_extrem(void **state) 
{ 
    assert_int_equal( MOD256(2147483647) , 255 );
    assert_int_equal( MOD256(-2147483648) , 0 );
}

static void test_negatif(void **state)
{
    assert_int_equal( MOD256(-300) , -44 );
}
    
    

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_zero),
        cmocka_unit_test(test_extrem),
        cmocka_unit_test(test_negatif),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
