#ifndef DW_COMPONENT_H
#define DW_COMPONENT_H

typedef struct ComponentItem ComponentItem;
typedef struct ComponentList ComponentList;

#include "entity.h"


typedef enum {
    CAMERA      = (1 << 0),
    PHYSIC      = (1 << 1),
    TRANSFORM   = (1 << 2),
    SPRITE      = (1 << 3),
    MESH        = (1 << 4),
    SCRIPT      = (1 << 5)
} ComponentType;


struct ComponentItem {
    void* id;
    ComponentType type;
    Entity* entity;

    ComponentItem* next;
};


void componentlist_clear(ComponentList* list);
void componentlist_pop(ComponentList* list, ComponentItem* item);
ComponentItem* componentlist_push(ComponentList* list, void* id, ComponentType type, Entity* entity);
void component_free(ComponentItem* item);


#endif
