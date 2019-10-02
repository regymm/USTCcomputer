/**
 * File              : hw9.c
 * License           : GPL-3.0-or-later
 * Author            : Yimin Gu <github.com/ustcpetergu>
 * Date              : 2019.10.01
 * Last Modified Date: 2019.10.02
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

// first, uniform dist. in [0, 1], mu = 0.5
double f1(){
	return randreal();
}


// second function, simulate binomial dist. 
// expectation mu = 0.5
double f2()
{
	return (randreal() > 0.5) ? 0 : 1;

}

// third and last, Guass dist. w/ different mu and simga from std. Gauss dist. 
double f3()
{
	double mu = 0;
	double sigma = 0.1;
	return (1 / sigma) * sqrt(-2 * log(randreal())) * cos(2 * M_PI * randreal());
}


void calc(int N, double f(), double mean)
{
	int M = 500000;
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
	/*calc(10, f1, 0.5);*/
	/*calc(50000, f2, 0.5);*/
	calc(50, f3, 0.);
	return 0;
}
