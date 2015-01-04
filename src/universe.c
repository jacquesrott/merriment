#include <SDL2/SDL.h>
#include <stdlib.h>

#include "universe.h"


UniTree* unitree_create() {
    UniTree* tree = malloc(sizeof(*tree));
    tree->root = NULL;
    return tree;
}


void unitree_destroy(UniTree* tree) {
    if(tree->root->next) {
        unode_destroy(tree->root->next);
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION,
            "Root had \"next\" node, warning memory leak possible");
    }
    if(tree->root->previous) {
        unode_destroy(tree->root->next);
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION,
            "Root had \"previous\" node, warning memory leak possible");
    }
    unode_destroy(tree->root);
    free(tree);
}


UNode* unitree_v2_in(const UniTree* tree, const vec2* point) {
    return unode_v2_in(tree->root, point);
}


UNode* unode_v2_in(UNode* node, const vec2* point) {
    if(node == NULL) return NULL;

    int cmp = v2_in_c2(point, &node->box);

    if(cmp == 1) {
        return unode_v2_in(node->next, point);
    } else {
        UNode* child = unode_v2_in(node->head_child, point);
        return (child) ? child : node;
    }
}


UNode* unode_c2_in(UNode* node, const Circle2D* box) {
    if(node == NULL) return NULL;

    int cmp = c2_in_c2(box, &node->box);

    if(cmp == 1) {
        return unode_c2_in(node->next, box);
    } else {
        UNode* child = unode_c2_in(node->head_child, box);
        return (child) ? child : node;
    }
}


UNode* unitree_put(const UniTree* tree, Circle2D box, void* value, AOType type) {
    return unode_put(tree->root, box, value, type);
}


void unode_push(UNode* root, UNode* child) {
    if(root->head_child == NULL) root->head_child = child;
    if(root->tail_child) root->tail_child->next = child;

    child->previous = root->tail_child;
    root->tail_child = child;
    child->next = NULL;
    child->parent = root;

    root->children_length++;
}


void unode_rotate(UNode* node, UNode* root) {
    root->parent = node->parent;
    node->parent = root;

    if(root->parent && root->parent->head_child == node)
        root->parent->head_child = root;
    if(root->parent && root->parent->tail_child == node)
        root->parent->tail_child = root;

    if(node->next) {
        node->next->previous = root;
        root->next = node->next;
    }
    if(node->previous) {
        node->previous->next = root;
        root->previous = node->previous;
    }

    unode_push(root, node);
}


UNode* unode_put(UNode* node, Circle2D box, void* value, AOType type) {
    if(node == NULL) {
        return unode_create(box, value, type);
    }

    UNode* included_in = unode_c2_in(node, &box);
    if(included_in == NULL) {
        return NULL;
    }

    UNode* new_node = unode_create(box, value, type);

    if(included_in->head_child == NULL) {
        unode_push(included_in, new_node);
        return new_node;
    }

    UNode* new_child = included_in->head_child;
    while(new_child) {
        int cmp = c2_in_c2(&new_child->box, &box);
        if(cmp == 0) {
            unode_rotate(new_child, new_node);
            new_child = new_node->next;
            continue;
        }
        new_child = new_child->next;
    }
    return new_node;
}


UNode* unode_create(Circle2D box, void* value, AOType type) {
    UNode* node = malloc(sizeof(*node));
    node->object = value;
    node->box = box;
    node->type = type;
    node->children_length = 0;

    node->parent = NULL;
    node->head_child = NULL;
    node->tail_child = NULL;
    node->next = NULL;
    node->previous = NULL;

    return node;
}


void unode_destroy(UNode* node) {
    UNode* next = node->head_child;
    while(next) {
        UNode* new_next = next->next;
        unode_destroy(next);
        next = new_next;
    }
    free(node);
}


char* aotype_to_str(AOType type) {
    switch(type) {
        case AO_GALAXY:
            return "Galaxy";
        case AO_GALACTIC_REGION:
            return "Galactic region";
        case AO_STAR:
            return "Star";
        case AO_GAS_PLANET:
            return "Gas planet";
        case AO_PLANET:
            return "Planet";
        case AO_GAS_MOON:
            return "Gas moon";
        case AO_MOON:
            return "Moon";
        case AO_ASTEROID:
            return "Asteroid";
        default:
            return NULL;
    }
}
