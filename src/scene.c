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
    transformpool_destroy(scene->transforms);
    scriptpool_destroy(scene->scripts);
    entitypool_destroy(scene->entities);
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



void scene_serialize(Scene* scene, const char* path) {
    FILE *file = NULL;
    file = fopen(path, "w+b");
    if(file == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open %s. ERROR: %d\n", path, errno);
    }


    fclose(file);
}


void scene_deserialize(Scene* scene, const char* path) {
    FILE *file = NULL;
    cmp_ctx_t context;
    uint32_t key_count;
    char key[32];
    uint32_t key_len;

    file = fopen(path, "r+b");
    if(file == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open %s. ERROR: %d\n", path, errno);
    }

    cmp_init(&context, file, file_reader, file_writer);
    cmp_read_map(&context, &key_count);

    while(--key_count) {
        key_len = sizeof(key);
        cmp_read_str(&context, key, &key_len);
        key[key_len] = 0;

        if(strcmp("path", key) == 0) {
            uint32_t path_len = 65;
            cmp_read_str(&context, scene->path, &path_len);
        } else if (strcmp("entities", key) == 0) {
            uint32_t entities_size;
            cmp_read_array(&context, &entities_size);

            int i;
            for(i = 0; i < entities_size ; ++i) {
                Entity* entity = entitypool_add(scene->entities);
                entity_deserialize(entity, scene, &context);
            }
        }
    }

    fclose(file);
}
