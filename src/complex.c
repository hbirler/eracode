#include "complex.h"

void fill_complex(struct complex *c, float r, float i)
{
	//fills complex struct with given values
	c->real = r;
	c->imag = i;
}

void output_complex(struct complex *c)
{
	//outputs complex number in a nice way for debugging
	printf("%f + %fi\n", c->real, c->imag);
}