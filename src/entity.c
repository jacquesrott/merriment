#include <SDL2/SDL.h>
#include <stdlib.h>

#include "entity.h"
#include "pool.h"


Pool* entitypool_create() {
    unsigned int item_size = sizeof(Entity);
    return pool_create(
        item_size,
        MAX_ENTITIES,
        (void (*)(void*)) entity_destroy);
}


void* entitypool_add(Pool* pool) {
    Entity* item = pool_pop_available(pool);
    if(item == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "EntityPool stack overflow.\n");
        return NULL;
    }

    item->L = luaL_newstate();
    luaL_openlibs(item->L);

    item->components.head = NULL;
    item->components.count = 0;

    return item;
}


void entity_free(Entity* entity) {
    componentlist_clear(&entity->components);
}


void entity_destroy(Entity* entity) {
    componentlist_clear(&entity->components);
    lua_close(entity->L);
    pool_set_available(entity->pool.container, (PoolObject*) entity);
}


void entity_serialize(Entity* entity, Scene* scene, cmp_ctx_t* context) {
    cmp_write_map(context, 2);

    cmp_write_str(context, "name", 4);
    cmp_write_str(context, entity->name, strlen(entity->name));

    cmp_write_str(context, "components", 10);
    cmp_write_array(context, entity->components.count);

    ComponentItem* component = entity->components.head;

    while(component != NULL) {
        component_serialize(component, entity, scene, context);
        component = component->next;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Entity `%s` serialized.\n", entity->name);
}


void entity_deserialize(Entity* entity, Scene* scene, cmp_ctx_t* context) {
    uint32_t key_count;
    char key[32];
    uint32_t key_len;

    cmp_read_map(context, &key_count);

    int k;
    for(k = 0 ; k < key_count ; ++k) {
        key_len = sizeof(key);
        cmp_read_str(context, key, &key_len);
        key[key_len] = 0;

        if(strcmp("name", key) == 0) {
            uint32_t name_len = 65;
            cmp_read_str(context, entity->name, &name_len);
            entity->name[name_len] = 0;
        } else if(strcmp("components", key) == 0) {
            uint32_t components_size;
            cmp_read_array(context, &components_size);

            int i;
            for(i = 0 ; i < components_size ; ++i) {
                component_deserialize(entity, scene, context);
            }
        }
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Entity `%s` deserialized.\n", entity->name);
}
