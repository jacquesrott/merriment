#include <stdio.h>
#include <stdlib.h>

#include "../universe.h"
#include "../almath.h"


void check_node(UNode* node, char* message, int length, UNode* parent, UNode* next, UNode* previous, UNode* head, UNode* tail) {
    printf("\n--------------\n%s\n", message);
    sput_fail_unless(node->children_length == length, "CHILDREN_LENGTH");
    sput_fail_unless(node->parent == parent, "PARENT");
    sput_fail_unless(node->next == next, "NEXT");
    sput_fail_unless(node->previous == previous, "PREVIOUS");
    sput_fail_unless(node->head_child == head, "HEAD_CHILD");
    sput_fail_unless(node->tail_child == tail, "TAIL_CHILD");
    printf("--------------\n");
}


void test_universe_unode() {
    Circle2D c = {
        {0, 0},
        1000
    };
    char object[] = "test";
    UNode* root = unode_create(c, &object, AO_GALAXY);

    sput_fail_unless(root->box.radius == c.radius, "Node has proper box set to 1000");
    sput_fail_unless(root->object == &object, "Node has proper object set to object pointer");
    sput_fail_unless(root->type == AO_GALAXY, "Node has proper type set to AO_GALAXY");
    check_node(
        root,
        "root is properly set",
        0, NULL, NULL, NULL, NULL, NULL);

    c.position.x = -500;
    c.radius = 500;
    UNode* child = unode_create(c, NULL, AO_GALACTIC_REGION);
    unode_push(root, child);

    check_node(
        root,
        "root as child set to head_child and tail_child an len 1",
        1, NULL, NULL, NULL, child, child);
    check_node(
        child,
        "child parent set to root and len 0",
        0, root, NULL, NULL, NULL, NULL);

    c.position.x = 500;
    c.radius = 500;
    UNode* child_tail = unode_create(c, NULL, AO_GALACTIC_REGION);
    unode_push(root, child_tail);

    check_node(
        root,
        "root has 2 children, child as head and child_tail as tail",
        2, NULL, NULL, NULL, child, child_tail);
    check_node(
        child,
        "child has next as child_tail and root as parent",
        0, root, child_tail, NULL, NULL, NULL);
    check_node(
        child_tail,
        "child_tail has child as previous and NULL as next",
        0, root, NULL, child, NULL, NULL);

    c.radius = 250;
    c.position.x = -750;
    UNode* child_child_head = unode_create(c, NULL, AO_STAR);
    unode_push(child, child_child_head);

    c.radius = 5;
    UNode* result = unode_v2_in(root, &c.position);

    sput_fail_unless(
        result == child_child_head,
        "child_child_head is found when targeting a point");

    c.radius = 5;
    c.position.x = -250;
    result = unode_v2_in(root, &c.position);

    sput_fail_unless(
        result == child,
        "child is found when targeting a point");

    c.position.x = 10000;
    result = unode_v2_in(root, &c.position);
    sput_fail_unless(
        result == NULL,
        "NULL is found when targeting a point which is in not in tree");

    c.radius = 5;
    c.position.x = -250;
    result = unode_c2_in(root, &c);

    sput_fail_unless(
        result == child,
        "child is found when looking for the circle including the one specified");
    c.radius = 100000;
    c.position.x = -0;
    result = unode_c2_in(root, &c);

    sput_fail_unless(
        result == NULL,
        "NULL is found when looking for the circle specified is bigger than the root tree");

    c.radius = 5;
    c.position.x = -2000;
    result = unode_c2_in(root, &c);

    sput_fail_unless(
        result == NULL,
        "NULL is found when looking for a circle which is not included into the tree");

    c.radius = 750;
    c.position.x = -250;
    UNode* new_node = unode_put(root, c, NULL, AO_MOON);

    check_node(
        root,
        "root has new head_child, which is new_node and still child_tail as tail",
        2, NULL, NULL, NULL, new_node, child_tail);
    check_node(
        child,
        "child has now new_node as parent and not child_tail as next",
        1, new_node, NULL, NULL, child_child_head, child_child_head);
    check_node(
        new_node,
        "new_node has root as parent, child_tail as next, child as tail and head",
        1, root, child_tail, NULL, child, child);
    check_node(
        child_tail,
        "child_tail has root as parent, new_node as previous",
        0, root, NULL, new_node, NULL, NULL);

    c.radius = 250;
    c.position.x = 750;
    UNode* new_tail_node = unode_put(root, c, NULL, AO_MOON);
    check_node(
        child_tail,
        "child_tail has root as parent, new_node as previous, new_tail_node as head and tail child and len as 1",
        1, root, NULL, new_node, new_tail_node, new_tail_node);
    check_node(
        new_tail_node,
        "new_tail_node has child_tail as parent",
        0, child_tail, NULL, NULL, NULL, NULL);

    c.position.x = 3000;
    UNode* null_node = unode_put(root, c, NULL, AO_GALAXY);
    sput_fail_unless(null_node == NULL, "Circle outside root is not inserted and returns NULL.");

    printf("Cleaning memory...\n");
    unode_destroy(root);
}
