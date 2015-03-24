#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>


#include "cmp.h"
#include "scene.h"
#include "component.h"


Scene* scene_create() {
    Scene* scene = malloc(sizeof(*scene));
    scene->space = cpSpaceNew();
    scene->entities = entitypool_create();
    scene->transforms = transformpool_create();
    scene->sprites = spritepool_create();
    scene->scripts = scriptpool_create();
    return scene;
}


void scene_destroy(Scene* scene) {
    cpSpaceFree(scene->space);

    // entities has to be first, because of relation with components
    pool_destroy(scene->entities);
    pool_destroy(scene->transforms);
    pool_destroy(scene->scripts);
    pool_destroy(scene->sprites);
    free(scene);
}


static bool read_bytes(void *data, size_t sz, FILE *fh) {
    return fread(data, sizeof(uint8_t), sz, fh) == (sz * sizeof(uint8_t));
}


static bool file_reader(cmp_ctx_t *ctx, void *data, size_t limit) {
    return read_bytes(data, limit, (FILE *)ctx->buf);
}


static size_t file_writer(cmp_ctx_t *ctx, const void *data, size_t count) {
    return fwrite(data, sizeof(uint8_t), count, (FILE *)ctx->buf);
}


void scene_save(Scene* scene, const char* path) {
    FILE *file = NULL;
    cmp_ctx_t context;
    file = fopen(path, "w+b");
    if(file == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open %s. ERROR: %d\n", path, errno);
    }

    cmp_init(&context, file, file_reader, file_writer);

    scene_serialize(scene, &context);

    fclose(file);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Scene `%s` serialized.\n", scene->path);
}


void scene_serialize(Scene* scene, cmp_ctx_t* context) {
    cmp_write_map(context, 2);
    cmp_write_str(context, "path", 4);
    cmp_write_str(context, scene->path, strlen(scene->path));

    cmp_write_str(context, "entities", 8);
    cmp_write_array(context, scene->entities->count);
    Entity* entity = scene->entities->allocated;

    while(entity != NULL) {
        entity_serialize(entity, scene, context);
        entity = entity->pool.next;
    }
}


void scene_load(Scene* scene, const char* path) {
    FILE *file = NULL;
    cmp_ctx_t context;

    file = fopen(path, "r+b");
    if(file == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open %s. ERROR: %d\n", path, errno);
    }

    cmp_init(&context, file, file_reader, file_writer);

    scene_deserialize(scene, &context);

    fclose(file);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Scene %s loaded.\n", path);
}


void scene_deserialize(Scene* scene, cmp_ctx_t* context) {
    uint32_t key_count;
    char key[32];
    uint32_t key_len;

    cmp_read_map(context, &key_count);

    int k;
    for(k = 0 ; k < key_count ; ++k) {
        key_len = sizeof(key);
        cmp_read_str(context, key, &key_len);
        key[key_len] = 0;

        if(strcmp("path", key) == 0) {
            uint32_t path_len = 65;
            cmp_read_str(context, scene->path, &path_len);
            scene->path[path_len] = 0;
        } else if (strcmp("entities", key) == 0) {
            uint32_t entities_size;
            cmp_read_array(context, &entities_size);

            int i;
            for(i = 0; i < entities_size ; ++i) {
                Entity* entity = entitypool_add(scene->entities);
                entity_deserialize(entity, scene, context);
            }
        } else if(strcmp("source", key) == 0) {
            uint32_t source_len = 65;
            char source[source_len];
            cmp_read_str(context, source, &source_len);
        }
    }
}
