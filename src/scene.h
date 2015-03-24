#ifndef DW_SCENE_H
#define DW_SCENE_H

#include <chipmunk/chipmunk.h>

typedef struct Scene Scene;

#include "pool.h"
#include "entity.h"
#include "components/script.h"
#include "components/transform.h"
#include "components/sprite.h"


struct Scene {
//    Camera camera;
    cpSpace* space;

    Pool* entities;

    Pool* transforms;
    Pool* scripts;
//    PhysicPool* physics;
//    MeshPool* meshes;
    Pool* sprites;
    char path[64];
};


Scene* scene_create();
void scene_destroy(Scene* scene);
void scene_save(Scene* scene, const char* path);
void scene_serialize(Scene* scene, cmp_ctx_t* context);
void scene_load(Scene* scene, const char* path);
void scene_deserialize(Scene* scene, cmp_ctx_t* context);


#endif
