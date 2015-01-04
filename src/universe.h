#ifndef DW_UNIVERSE_H
#define DW_UNIVERSE_H

#include "physic.h"

typedef enum {
    AO_GALAXY,
    AO_GALACTIC_REGION,
    AO_STAR,
    AO_GAS_PLANET,
    AO_PLANET,
    AO_GAS_MOON,
    AO_MOON,
    AO_ASTEROID,
} AOType;


typedef struct UNode UNode;

struct UNode {
    Circle2D box;
    void* object;
    AOType type;

    UNode* parent;

    UNode* next;
    UNode* previous;

    UNode* head_child;
    UNode* tail_child;

    int children_length;
};


typedef struct {
    UNode* root; 
} UniTree;


UniTree* unitree_create();
void unitree_destroy(UniTree* tree);

UNode* unitree_v2_in(const UniTree* tree, const vec2* point);
UNode* unitree_put(const UniTree* tree, Circle2D box, void* value, AOType type);


UNode* unode_create(Circle2D box, void* value, AOType type);
void unode_destroy(UNode* node);

UNode* unode_v2_in(UNode* node, const vec2* point);
UNode* unode_c2_in(UNode* node, const Circle2D* box);
void unode_push(UNode* root, UNode* child);
void unode_rotate(UNode* node, UNode* root);
UNode* unode_put(UNode* node, Circle2D box, void* value, AOType type);

char* aotype_to_str(AOType type);

#endif
