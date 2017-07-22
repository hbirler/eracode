#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>

struct complex
{
	float real;
	float imag;
};

void fill_complex(struct complex *c, float r, float i);

void output_complex(struct complex *c);

#endif