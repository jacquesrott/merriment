#ifndef DW_CONFIG_H
#define DW_CONFIG_H

#define DW_OPENGL_MAJOR_VERSION 3
#define DW_OPENGL_MINOR_VERSION 3
#define DW_DEPTH_SIZE 24
#define DW_DOUBLEBUFFER 1


#define DW_PLANET_MIN_RADIUS 100.0
#define DW_PLANET_MAX_RADIUS 400.0
#define DW_PLANET_RADIUS_DIFF 15.0


#define DW_DEFAULT_SCENE "assets/scenes/scene.mp"


#define MAX_COMPONENTS 32
#define MAX_ENTITIES 128
#define MAX_SCRIPTS MAX_ENTITIES * 2
#define MAX_TRANSFORMS MAX_ENTITIES
#define MAX_PHYSICS MAX_ENTITIES
#define MAX_RENDERERS MAX_ENTITIES

#endif
