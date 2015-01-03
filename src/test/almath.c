#include <stdio.h>
#include "../almath.h"


void test_almath_v2() {
    vec2 v = {5, 5};
    float length = v2_length(&v);
    float expected = 7.071067811865475;
    sput_fail_unless(length == expected, "v2_length computes proper length");
}


void test_almath_v3() {
    vec3 v = {20, 10, 20};
    float length = v3_length(&v);
    sput_fail_unless(length == 30, "v3_length computes proper length");
}


void test_almath_v4() {
    vec4 v = {20, 10, 20, 10};
    float length = v4_length(&v);
    float expected = 31.6227766016838;
    sput_fail_unless(length == expected, "v4_length computes proper length");
}
