#ifndef COPS_H
#define COPS_H
#include <math.h>

#include "complex.h"

void conj_c(struct complex *z, struct complex *conj_z);
float norm_c(struct complex *z);
#endif