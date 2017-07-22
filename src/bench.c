#include "bench.h"

void run_conj_single(float r, float i, int is_asm)
{
	struct complex a, asmres, cres;
	fill_complex(&a, r, i);
	
	if (is_asm)
		conj_asm(&a, &asmres);
	else
		conj_c(&a, &cres);
}

void run_norm_single(float r, float i, int is_asm)
{
	struct complex a;
	fill_complex(&a, r, i);
	
	if (is_asm)
		norm_asm(&a);
	else
		norm_c(&a);
}

struct bench_result_single bench_conj_single(int run_count, int is_asm)
{
	clock_t t;
	t = clock();
	
	int testcount = 0;
	for (int k = 0; k < run_count; k++)
	{
		for (int realind = 0; realind < FLOATSETSIZE; realind++)
		for (int imagind = 0; imagind < FLOATSETSIZE; imagind++)
		{
			run_conj_single(floatset[realind], floatset[imagind], is_asm);
			testcount += 1;
		}
	}
	
	t = clock() - t;
	double elapsed = ((double)t)/CLOCKS_PER_SEC;
	
	struct bench_result_single result;
	result.total_time = elapsed;
	result.avg_time = elapsed / testcount;
	
	return result;
}

struct bench_result_single bench_norm_single(int run_count, int is_asm)
{
	clock_t t;
	t = clock();
	
	int testcount = 0;
	for (int k = 0; k < run_count; k++)
	{
		for (int realind = 0; realind < FLOATSETSIZE; realind++)
		for (int imagind = 0; imagind < FLOATSETSIZE; imagind++)
		{
			run_norm_single(floatset[realind], floatset[imagind], is_asm);
			testcount += 1;
		}
	}
	
	t = clock() - t;
	double elapsed = ((double)t)/CLOCKS_PER_SEC;
	
	struct bench_result_single result;
	result.total_time = elapsed;
	result.avg_time = elapsed / testcount;
	
	return result;
}

struct bench_result bench_conj()
{
	struct bench_result result;
	result.asm = bench_conj_single(RUN_COUNT, 1);
	result.c = bench_conj_single(RUN_COUNT, 0);
	return result;
}

struct bench_result bench_norm()
{
	struct bench_result result;
	result.asm = bench_norm_single(RUN_COUNT, 1);
	result.c = bench_norm_single(RUN_COUNT, 0);
	return result;
}