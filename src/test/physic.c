#include "../physic.h"


void test_physic_circle() {
    int result;
    Circle2D c_a = {
        .position={
            .x=2.0,
            .y=3.0
        },
        .radius=2.0
    };
    vec2 v = {2.0, 2.0};

    result = v2_in_c2(&v, &c_a);
    sput_fail_unless(result == 0, "v2_in_c2 returns 0 when point in circle.");

    v.x = 1.0;
    v.y = 1.0;
    result = v2_in_c2(&v, &c_a);
    sput_fail_unless(result == 1, "v2_in_c2 returns 1 when point not in circle.");

    v.x = 2.0;
    v.y = 1.0;
    result = v2_in_c2(&v, &c_a);
    sput_fail_unless(result == 1, "v2_in_c2 returns 1 when point on limit of circle.");

    Circle2D c_b = {
        .position={
            .x=10.0,
            .y=15.0
        },
        .radius=10.0
    };
    result = c2_in_c2(&c_a, &c_b);
    sput_fail_unless(result == 1, "c2_in_c2 returns 1 when circle are not overlapping.");

    result = c2_collide(&c_a, &c_b);
    sput_fail_unless(result == 1, "c2_collide returns 1 when circle are not overlapping.");

    c_b.position.y = 10;
    result = c2_in_c2(&c_a, &c_b);
    sput_fail_unless(result == 1, "c2_in_c2 returns 1 when circle are only overlapping.");

    result = c2_collide(&c_a, &c_b);
    sput_fail_unless(result == 0, "c2_collide returns 0 when circle are only overlapping.");

    c_b.position.x = 0;
    c_b.position.y = 0;
    result = c2_in_c2(&c_a, &c_b);
    sput_fail_unless(result == 0, "c2_in_c2 returns 0 when circle are overlapping and c_a in c_b.");

    result = c2_collide(&c_a, &c_b);
    sput_fail_unless(result == 0, "c2_collide returns 0 when circle are overlapping and c_a in c_b.");

    result = c2_in_c2(&c_b, &c_a);
    sput_fail_unless(result == 0, "c2_in_c2 returns 0 when checking with inverted query.");

    result = c2_collide(&c_b, &c_a);
    sput_fail_unless(result == 0, "c2_collide returns 0 when checking with inverted query.");
}
