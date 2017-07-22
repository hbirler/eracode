#ifndef BENCH_H
#define BENCH_H

#include <time.h>

#include "complex.h"
#include "asmops.h"
#include "cops.h"
#include "dataset.h"

#define RUN_COUNT 10000

struct bench_result_single
{
	double total_time;
	double avg_time;
};

struct bench_result
{
	struct bench_result_single asm;
	struct bench_result_single c;
};

struct bench_result bench_conj();

struct bench_result bench_norm();

#endif