#ifndef ASMOPS_H
#define ASMOPS_H

#include "complex.h"

void conj_asm(struct complex *z, struct complex *conj_z);
float norm_asm(struct complex *z);

#endif