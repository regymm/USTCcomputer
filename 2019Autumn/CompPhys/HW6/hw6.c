/**
 * File              : hw6.c
 * License           : GPL-3.0-or-later
 * Author            : Yimin Gu <github.com/ustcpetergu>
 * Date              : 2019.09.29
 * Last Modified Date: 2019.09.30
 * ---
 * Computational physics homework 6
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// some constants, as is said in hw6.md
double A = 0.96;
double B = 0.398943;
// range is [-5, 5]
// calculate these only once
double Pm5;
double P5;
double eps = 1e-5;

// p(x), the target
double p(double x)
{
	return B * exp(- x * x / 2);
}

// F(x), the Lorentz-like
double F(double x)
{
	return A / (1 + pow(x, 4));
}

// G is indefinite integral of F, used to calculate P
double G(double x)
{
	if(x < -5 - eps || x > 5 + eps)
		exit(-1);
	return A * 1/(4*sqrt(2)) * (-log(x*x - sqrt(2)*x +1) +\
			log(x*x + sqrt(2)*x + 1) -\
			2 * atan(1 - sqrt(2)*x) +\
			2 * atan(sqrt(2)*x + 1));
}

// P, PDF of F
double P(double x)
{
	return G(x) - G(-5);
}

// Binary search to caculate the value of monotonous function P^{-1}
double Preverse(double t)
{
	if(t < Pm5 - eps || t > P5 + eps)
		exit(-1);
	double l = -5;
	double r = 5;
	double m = 0;
	double eps = 1e-5;
	while(r - l > eps) {
		m = (l + r) / 2;
		/*printf("->%lf, %lf %lf %lf %lf\n", t, P(m), l, m, r);*/
		if(P(m) > t)
			r = m;
		else
			l = m;
	}
	/*printf("In P-1: %lf\n", m);*/
	return m;
}

// random real number in [0, 1]
double randreal()
{
	return (double) rand() / (RAND_MAX);
}

// get a random number under distribution p(x), return 9999 if fail
// procedure described in hw6.md
double get1()
{
	double alpha = (P5 - Pm5) * randreal() + Pm5;
	double beta = Preverse(alpha);
	double gamma = F(beta) * randreal();
	if(gamma < p(beta))
		return beta;
	else
		/*return beta;*/
		return 9999;


}
// get a random number (p1, p2), accept resized p1 \in [-5,5] if p2*max(p) falls in [0,p(p1)]
double get2()
{
	double p1 = randreal() * 10 - 5;
	double p2 = randreal() * B;
	if(p2 < p(p1))
		return p1;
	else
		return 9999;
}

int main(int argc, char* argv[])
{
	P5 = P(5);
	Pm5 = P(-5);
	/*printf("%lf\n", Preverse(P(5)));*/
	/*printf("%lf\n", P5);*/
	/*printf("%lf\n", P(-5));*/
	/*printf("%lf\n", P(0));*/
	/*printf("%lf\n", Preverse(2.1274));*/
	srand((unsigned)time(0));
	int i;
	int N = 300000;
	int cnt = 0;
	double t;
	if(argc != 2) {
		fprintf(stderr, "%s (task1|task2)\n", argv[0]);
		exit(-2);
	}
	else if (strcmp(argv[1], "task1") == 0) {
		// task1: 舍选法+变换抽样
		/*for(i = 0; i < 101; i++)*/
			/*printf("%lf\n", Preverse((double)i/101 * P5));*/
			/*printf("%lf\n", P((double) i / 10 - 5));*/
		for(i = 0; i < N; i++) {
			t = get1();
			if(t < 9990) {
				printf("%lf,", t);
				cnt++;
			}
		}
		// calculate the efficiency
		// to avoid mess up with output, print this to stderr
		fprintf(stderr, "Accept rate: %lf\n", (double)cnt / N);
	}
	else if(strcmp(argv[1], "task2") == 0) {
		// task2: 直接舍选法抽样
		for(i = 0; i < N; i++) {
			t = get2();
			if(t < 9990) {
				printf("%lf,", t);
				cnt++;
			}
		}
		// calculate the efficiency
		// to avoid mess up with output, print this to stderr
		fprintf(stderr, "Accept rate: %lf\n", (double)cnt / N);
	}
	// result generation: 
	// `./a.out task1 | sed s'/.$//' > data.csv`
	// use the calc.nb to read the data.csv
	return 0;
}

