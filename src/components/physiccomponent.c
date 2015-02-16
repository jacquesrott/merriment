#include <stdlib.h>

#include "physiccomponent.h"


PhysicComponent* physiccomponent_create() {
    PhysicComponent* component = malloc(sizeof(*component));
    return component;
}


void physiccomponent_destroy(PhysicComponent* component) {
    free(component);
}
