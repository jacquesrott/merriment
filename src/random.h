#ifndef DW_RANDOM_H
#define DW_RANDOM_H

int rand_rangei(int min, int max);
float rand_rangef(float min, float max);

#define rand_bool() rand_rangei(0, 2)

#endif
