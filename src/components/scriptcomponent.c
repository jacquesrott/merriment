#include <stdlib.h>

#include "scriptcomponent.h"


ScriptComponent* scriptcomponent_create() {
    ScriptComponent* component = malloc(sizeof(*component));
    return component;
}


void scriptcomponent_destroy(ScriptComponent* component) {
    free(component);
}
