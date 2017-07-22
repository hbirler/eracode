#include "cops.h"

#include <math.h>

void conj_c(struct complex *z, struct complex *conj_z)
{
	conj_z->real = z->real;
	conj_z->imag = -z->imag;
}

float norm_c(struct complex *z)
{
	//we choose to output NaN when real or imag is NaN
	//which is not always the case in the standard library
	if (isnan(z->real) || isnan(z->imag))
		return NAN;
	return hypot(z->real, z->imag);
}