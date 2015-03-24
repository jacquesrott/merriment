#include <stdlib.h>
#include <SDL2/SDL.h>

#include "component.h"

#include "components/physic.h"
#include "components/transform.h"
#include "components/script.h"
#include "components/sprite.h"



void componentlist_clear(ComponentList* list) {
    ComponentItem* item = list->head;

    while(item) {
        ComponentItem* next = item->next;
        component_free(item);
        item = next;
    }
    list->count = 0;
    list->head = NULL;
}


void componentlist_pop(ComponentList* list, ComponentItem* item) {
    ComponentItem* cursor = list->head;

    if(cursor == item) {
        list->head = item->next;
        component_free(item);
        --list->count;
        return;
    }

    while(cursor) {
        if(cursor->next == item) {
            cursor->next = item->next;
            component_free(item);
            --list->count;
            return;
        }
        cursor = cursor->next;
    }
}


ComponentItem* componentlist_push(ComponentList* list, void* id, ComponentType type, Entity* entity) {
    ComponentItem* item = malloc(sizeof(*item));
    item->id = id;
    item->type = type;
    item->entity = entity;
    item->next = list->head;
    list->head = item;
    ++list->count;
    return item;
}


void component_free(ComponentItem* item) {
    switch(item->type) {
        case CAMERA:
            break;
        case PHYSIC:
            break;
        case TRANSFORM:
            transformcomponent_destroy(item->id);
            break;
        case SPRITE:
            spritecomponent_destroy(item->id);
            break;
        case MESH:
            break;
        case SCRIPT:
            scriptcomponent_destroy(item->id);
            break;
        default:
            break;
    }
    free(item);
}


void component_serialize(ComponentItem* component, Entity* entity, Scene* scene, cmp_ctx_t* context) {
    cmp_write_array(context, 2);
    cmp_write_uint(context, component->type);

    switch(component->type) {
        case CAMERA:
            break;
        case PHYSIC:
            break;
        case TRANSFORM:
            transformcomponent_serialize(component->id, context);
            break;
        case SPRITE:
            spritecomponent_serialize(component->id, context);
            break;
        case MESH:
            break;
        case SCRIPT:
            scriptcomponent_serialize(component->id, entity->L, context);
            break;
        default:
            break;
    }
}


void component_deserialize(Entity* entity, Scene* scene, cmp_ctx_t* context) {
    uint32_t size;
    cmp_read_array(context, &size);

    if(size != 2) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Malformed component.\n");
        return;
    }

    ComponentType type;
    cmp_read_int(context, (int32_t*) &type);

    switch(type) {
        case CAMERA:
            break;
        case PHYSIC:
            break;
        case TRANSFORM:
            transformcomponent_deserialize(entity, scene->transforms, context);
            break;
        case SPRITE:
            spritecomponent_deserialize(entity, scene->sprites, context);
            break;
        case MESH:
            break;
        case SCRIPT:
            scriptcomponent_deserialize(entity, scene->scripts, context);
            break;
        default:
            break;
    }
}
