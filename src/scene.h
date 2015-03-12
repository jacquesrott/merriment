#ifndef DW_SCENE_H
#define DW_SCENE_H

#include <chipmunk/chipmunk.h>

#include "entity.h"
#include "components/script.h"
#include "components/transform.h"


typedef struct {
//    Camera camera;
    cpSpace* space;

    EntityPool* entities;

    TransformPool* transforms;
    ScriptPool* scripts;
//    PhysicPool* physics;
//    MeshPool* meshes;
//    SpritePool* sprites;
} Scene;


Scene* scene_create();
void scene_destroy(Scene* scene);


#endif
