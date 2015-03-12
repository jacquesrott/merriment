#include <stdlib.h>

#include "scene.h"


Scene* scene_create() {
    Scene* scene = malloc(sizeof(*scene));
    scene->space = cpSpaceNew();
    scene->entities = entitypool_create();
    scene->transforms = transformpool_create();
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
