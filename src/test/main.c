#include <sput.h>

#include "almath.c"


int main(int argc, char** argv){
    sput_start_testing();

    sput_enter_suite("almath");
    sput_run_test(test_almath_v2);
    sput_run_test(test_almath_v3);
    sput_run_test(test_almath_v4);

    sput_finish_testing();
    return sput_get_return_value();
}
