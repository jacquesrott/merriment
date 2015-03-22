#ifndef DW_SCENE_H
#define DW_SCENE_H

#include <chipmunk/chipmunk.h>

typedef struct Scene Scene;

#include "entity.h"
#include "components/script.h"
#include "components/transform.h"
#include "components/sprite.h"


struct Scene {
//    Camera camera;
    cpSpace* space;

    EntityPool* entities;

    TransformPool* transforms;
    ScriptPool* scripts;
//    PhysicPool* physics;
//    MeshPool* meshes;
    SpritePool* sprites;
    char path[64];
};


Scene* scene_create();
void scene_destroy(Scene* scene);
void scene_serialize(Scene* scene, const char* path);
void scene_deserialize(Scene* scene, const char* path);


#endif
