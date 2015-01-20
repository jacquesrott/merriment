#include <stdlib.h>

#include "random.h"


int rand_rangei(int min, int max) {
    return rand() % (max - min) + min;
}


float rand_rangef(float min, float max) {
    return (rand() / (float) RAND_MAX) * (max - min) + min;
}
