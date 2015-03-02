#ifndef DW_TIMER_H
#define DW_TIMER_H

#define DW_DELTA_TIME 0.01


typedef struct {
    double t;
    double dt;
    double accumulator;
    double current_time;
    double new_time;
    double frame_time;
} Timer;


double get_time();

Timer* timer_create();
void timer_update(Timer* timer);
void timer_sync(Timer* timer);
void timer_destroy(Timer* timer);


#endif
