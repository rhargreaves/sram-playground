#include "cmocka_inc.h"

int main(void)
{
    const struct CMUnitTest tests[] = {
        // clang-format off

        // clang-format on
    };

    cmocka_set_test_filter("*");
    return cmocka_run_group_tests(tests, NULL, NULL);
}
