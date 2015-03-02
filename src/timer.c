#include <stdlib.h>
#include <SDL2/SDL.h>
#include <chipmunk/chipmunk.h>

#include "timer.h"


double get_time() {
    return SDL_GetTicks() / 1000.0;
}


Timer* timer_create() {
    Timer* timer = malloc(sizeof(*timer));

    timer->t = 0.0;
    timer->dt = DW_DELTA_TIME;

    timer->accumulator = 0.0;
    timer->current_time = get_time();
    return timer;
}


void timer_update(Timer* timer) {
    timer->new_time = get_time();
    timer->frame_time = timer->new_time - timer->current_time;
    timer->current_time = timer->new_time;

    timer->accumulator += timer->frame_time;
}


void timer_sync(Timer* timer) {
    timer->accumulator -= timer->dt;
    timer->t += timer->dt;
}


void timer_destroy(Timer* timer) {
    free(timer);
}
