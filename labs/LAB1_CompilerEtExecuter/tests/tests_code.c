#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "module_a_tester.h"

static void simple_test(void **state) {
    assert_int_equal( addition(10,23) , 33 );
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(simple_test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
