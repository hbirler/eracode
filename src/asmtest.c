#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "asmtest.h"
#include "asmops.h"
#include "complex.h"
#include "cops.h"
#include "dataset.h"

#define MAX(A,B) ((A)>(B)?(A):(B))
#define MIN(A,B) ((A)<(B)?(A):(B))

int isnan_bits( float value )
{
	//sometimes there are inconsistencies with the
	//standart implementation of isnan
	//so we have this extra implementations that checks the bits
	return ((*(uint32_t*)&value) & 0x7fffffff) > 0x7f800000;
}

double compare_float(float a, float b)
{
	//outputs difference between two floating point values
	//checks for special cases
	if ((isinf(a) && isinf(b)))
	{
		//if both are infinity check for sign equality
		if (a < 0 && b < 0)
			return 0.0;
		else if (a > 0 && b > 0)
			return 0.0;
		else if (a == 0 && b == 0)
			return 0.0;
		else
			return INFINITY;
	}
	//if both are nan return zero
	if (isnan(a) && isnan(b))
		return 0.0;
	if (isnan_bits(a) && isnan_bits(b))
		return 0.0;
	//do the calculation normally if no special cases
	return abs((double)a-(double)b);
}

int isequal_float(float a, float b)
{
	//compares two floating values for equality
	//checks for special cases
	if ((isinf(a) && isinf(b)))
	{
		//if both are infinity check for sign equality
		if (a < 0 && b < 0)
			return 1;
		else if (a > 0 && b > 0)
			return 1;
		else if (a == 0 && b == 0)
			return 1;
		else
			return 0;
	}
	//if both are nan they are equal
	if (isnan(a) && isnan(b))
		return 1;
	if (isnan_bits(a) && isnan_bits(b))
		return 1;
	//do the comparison normally if no special cases
	return a == b;
}

double test_conj_single(float r, float i)
{
	//runs conj_asm and conj_c on the complex (r,i)
	//returns difference in results
	struct complex a, asmres, cres;
	fill_complex(&a, r, i);
	
	conj_asm(&a, &asmres);
	conj_c(&a, &cres);
	
	if (!isequal_float(cres.real, asmres.real))
		return INFINITY;
	
	return compare_float(cres.imag, asmres.imag);
}

double test_norm_single(float r, float i)
{
	//runs norm_asm and norm_c on the complex (r,i)
	//returns difference in results
	struct complex a;
	fill_complex(&a, r, i);
	
	double resasm = norm_asm(&a);
	double resc = norm_c(&a);
	
	return compare_float(resasm, resc);
}

struct test_result test_conj()
{
	//runs tests for all possible pairs given the "floatset" dataset
	double sum = 0.0;
	double max = test_conj_single(floatset[0], floatset[0]);
	double min = test_conj_single(floatset[0], floatset[0]);
	int testcount = 0;
	for (int realind = 0; realind < FLOATSETSIZE; realind++)
	for (int imagind = 0; imagind < FLOATSETSIZE; imagind++)
	{
		double res = test_conj_single(floatset[realind], floatset[imagind]);
		sum += res;
		max = MAX(max, res);
		min = MIN(min, res);
		testcount += 1;
	}
	
	struct test_result result;
	result.avg_error = sum / testcount;
	result.max_error = max;
	result.min_error = min;
	
	return result;
}

struct test_result test_norm()
{
	//runs tests for all possible pairs given the "floatset" dataset
	double sum = 0.0;
	double max = test_norm_single(floatset[0], floatset[0]);
	double min = test_norm_single(floatset[0], floatset[0]);
	int testcount = 0;
	for (int realind = 0; realind < FLOATSETSIZE; realind++)
	for (int imagind = 0; imagind < FLOATSETSIZE; imagind++)
	{
		double res = test_norm_single(floatset[realind], floatset[imagind]);
		sum += res;
		max = MAX(max, res);
		min = MIN(min, res);
		testcount += 1;
	}
	
	struct test_result result;
	result.avg_error = sum / testcount;
	result.max_error = max;
	result.min_error = min;
	
	return result;
}

