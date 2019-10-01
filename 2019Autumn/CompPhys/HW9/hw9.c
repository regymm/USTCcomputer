/**
 * File              : hw9.c
 * License           : GPL-3.0-or-later
 * Author            : Yimin Gu <github.com/ustcpetergu>
 * Date              : 2019.10.01
 * Last Modified Date: 2019.10.01
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// random real number in [0, 1]
double randreal()
{
	return (double) rand() / (RAND_MAX);
}

// first function, simulate binomial dist. 
// expectation mu = 0.
double f1()
{
	/*if(randreal() > 0.5)*/
		/*return 1.;*/
	/*else*/
		/*return -1.;*/
	return randreal();

}


void calc(int N, double f(), double mean)
{
	int M = 100000;
	int j;
	for(j = 0; j < M; j++) {
		int i;
		double avg = 0;
		double avgsqr = 0;
		for(i = 0; i < N; i++) {
			double t = f();
			avg += t;
			avgsqr += t*t;
		}
		avg /= N;
		/*printf("->%lf\n", avg);*/
		avgsqr /= N;
		double result = (avg - mean) / ((sqrt(avgsqr - avg * avg)) / sqrt(N));
		printf("%lf\n", result);

	}
}

int main(int argc, char* argv[])
{
	srand((unsigned)time(0));
	calc(2, f1, 0.5);
	return 0;
}
