#include <stdlib.h>

#include "physic.h"


PhysicComponent* physiccomponent_create() {
    PhysicComponent* component = malloc(sizeof(*component));
    return component;
}


void physiccomponent_destroy(PhysicComponent* component) {
    free(component);
}
