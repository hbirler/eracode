#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bench.h"
#include "complex.h"
#include "asmtest.h"
#include "asmops.h"

void help(int argc, char* argv[])
{
	printf("Usage:\tproject [option] input\n");
	printf("\tproject help\t- show help\n");
	printf("\n");
	printf("\tproject test\t- runs all tests\n");
	printf("\tproject test conj\t- runs the conjugate tests\n");
	printf("\tproject test norm\t- runs the norm tests\n");
	printf("\n");
	printf("\tproject bench\t- runs all benchmarks\n");
	printf("\tproject bench conj\t- runs the conjugate benchmarks\n");
	printf("\tproject bench norm\t- runs the norm benchmarks\n");
	printf("\n");
	printf("\tproject run conj [real] [imag]\t- run conjugate on (real + i * imag)\n");
	printf("\tproject run norm [real] [imag]\t- run norm on (real + i * imag)\n");
	printf("\n");
	printf("\tproject bless\t- bless yoav\n");
}

void out_test_conj()
{
	struct test_result res = test_conj();
	printf("Conjugate test result:\n");
	printf(" Avg Error:\t%le\n", res.avg_error);
	printf(" Max Error:\t%le\n", res.max_error);
	printf(" Min Error:\t%le\n", res.min_error);
}

void out_test_norm()
{
	struct test_result res = test_norm();
	printf("Norm test result:\n");
	printf(" Avg Error:\t%le\n", res.avg_error);
	printf(" Max Error:\t%le\n", res.max_error);
	printf(" Min Error:\t%le\n", res.min_error);
}

void test(int argc, char* argv[])
{
	if (argc >= 3 && strcmp(argv[2], "conj") == 0)
	{
		out_test_conj();
	}
	else if (argc >= 3 && strcmp(argv[2], "norm") == 0)
	{
		out_test_norm();
	}
	else
	{
		//run both tests when no option is given
		out_test_conj();
		out_test_norm();
	}
}

void out_bench_conj()
{
	struct bench_result res = bench_conj();
	printf("Conjugate benchmark result:\n");
	printf(" Assembly:\n");
	printf("\tTotal:  \t%le\n", res.asm.total_time);
	printf("\tAverage:\t%le\n", res.asm.avg_time);
	printf(" C Implementation \\w Standard Library:\n");
	printf("\tTotal:  \t%le\n", res.c.total_time);
	printf("\tAverage:\t%le\n", res.c.avg_time);
}

void out_bench_norm()
{
	struct bench_result res = bench_norm();
	printf("Norm benchmark result:\n");
	printf(" Assembly:\n");
	printf("\tTotal:\t%le\n", res.asm.total_time);
	printf("\tAverage:\t%le\n", res.asm.avg_time);
	printf(" C Implementation \\w Standard Library:\n");
	printf("\tTotal:\t%le\n", res.c.total_time);
	printf("\tAverage:\t%le\n", res.c.avg_time);
}

void bench(int argc, char* argv[])
{
	if (argc >= 3 && strcmp(argv[2], "conj") == 0)
	{
		out_bench_conj();
	}
	else if (argc >= 3 && strcmp(argv[2], "norm") == 0)
	{
		out_bench_norm();
	}
	else
	{
		//run both benchmarks when no option is given
		out_bench_conj();
		out_bench_norm();
	}
}

void out_run_conj(float real, float imag)
{
	printf("Conjugate:\n");
	struct complex a, asmres;
	fill_complex(&a, real, imag);
	
	conj_asm(&a, &asmres);
	
	printf("\tinput: %f + %f * i\n", a.real, a.imag);
	printf("\toutput: %f + %f * i\n", asmres.real, asmres.imag);
}

void out_run_norm(float real, float imag)
{
	printf("Norm:\n");
	struct complex a;
	fill_complex(&a, real, imag);
	
	float res = norm_asm(&a);
	
	printf("\tinput: %f + %f * i\n", a.real, a.imag);
	printf("\toutput: %f\n", res);
}

void run(int argc, char* argv[])
{
	if (argc < 5)
	{
		printf("Not enough parameters!\n");
		return;
	}
	float real = atof(argv[3]);
	float imag = atof(argv[4]);
	
	if (argc >= 3 && strcmp(argv[2], "conj") == 0)
	{
		out_run_conj(real, imag);
	}
	else if (argc >= 3 && strcmp(argv[2], "norm") == 0)
	{
		out_run_norm(real, imag);
	}
	else
	{
		//run both tests when no valid option is given
		//such as "./project run both 3 4"
		out_run_conj(real, imag);
		out_run_norm(real, imag);
	}
}

void bless(int argc, char* argv[])
{
	//blesses yoav
	//self explanatory
	int count = 1;
	if (argc >= 3)
	{
		//bless one more time than required
		//to get on yoav's good side
		count = atoi(argv[2]) + 1;
	}
	
	for (int i = 0; i < count; i++)
		printf("all hail Yoav the wise\n");
}

#define COMMANDCOUNT 5

//list of available commands
char* commands[] = {"help","test","bench","run","bless"};
//corresponding function pointers for the commands
void (*functions[])(int,char*[]) = {help, test, bench, run, bless};

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		printf("Usage:\tproject [option] input\n");
		printf("\tTry 'project help' for more information.\n");
	}
	else if (argc >= 2)
	{
		char donecom = 0;
		//check if input is in the list of commands
		for (int i = 0; i < COMMANDCOUNT; i++)
		{
			if (strcmp(argv[1], commands[i]) == 0)
			{
				//run the corresponding command
				donecom = 1;
				functions[i](argc, argv);
				break;
			}
		}
		if (!donecom)	//if input is not in the list of commands
			printf("No such command!\n");
	}
}