#ifndef ASMTEST_H
#define ASMTEST_H

struct test_result
{
	double avg_error;
	double max_error;
	double min_error;
};

struct test_result test_conj();

struct test_result test_norm();

#endif