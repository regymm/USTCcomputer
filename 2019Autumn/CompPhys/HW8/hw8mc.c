/**
 * File              : hw8mc.c
 * License           : GPL-3.0-or-later
 * Author            : Yimin Gu <github.com/ustcpetergu>
 * Date              : 2019.10.01
 * Last Modified Date: 2019.10.01
 * computational physics HW8, Monte Carlo integral
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
/*
 * mma results
In[10]:= SetOptions[SelectedNotebook[], PrintPrecision -> 16]
res = NIntegrate[Sqrt[x + Sqrt[x]], {x, 0, 2}, AccuracyGoal -> 10]

Out[11]= 2.689521304816752

In[12]:= Integrate[
 Integrate[
  Integrate[
   Integrate[
    Integrate[6 - x^2 - y^2 - z^2 - u^2 - v^2, {v, 0, 1.3}], {u, 0, 
     2}], {z, 0, .9}], {y, 0, .8}], {x, 0, .9}]

Out[12]= 5.644080000000002
 */

// random real number in [0, 1]
double randreal()
{
	return (double) rand() / (RAND_MAX);
}

double randrange(double x, double y)
{
	return randreal() * (y - x) + x;
}

// normal MC method (average method in 3.pdf) to calculate the first integral
double first(int N)
{
	double a = 0;
	double b = 2;
	double sum = 0;
	double res;
	double x;
	int i;
	for(i = 0; i < N; i++) {
		x = (b - a) * randreal() + a;
		sum += sqrt(sqrt(x) + x);
	}
	res = (b - a) / N * sum;
	/*printf("Result: %lf\n", res);*/
	return res;
}

// multi-dimension integral, same. 
double second(int N)
{
	double sum = 0;
	double res;
	int i;
	for(i = 0; i < N; i++) {
		double x = randrange(0, 9./10.);
		double y = randrange(0, 4./5.);
		double z = randrange(0, 9./10.);
		double u = randrange(0, 2.);
		double v = randrange(0, 13./10.);
		sum += 6 - pow(x, 2) - pow(y, 2) - pow(z, 2) - pow(u, 2) - pow(v, 2);
	}
	res = (9./10.*4./5.*9./10.*2.*13./10.) / N * sum;
	/*printf("Result: %lf\n", res);*/
	return res;
}

int main(int argc, char* argv[])
{
	srand((unsigned)time(0));
	int i, j;
	int times = 100;
	// try with different N
	for(i = 3; i <= 6; i++) {
		int N = pow(10, i);
		printf("N: %d\n", N);
		double avg = 0;
		double avgsqr = 0;
		// for each N, do multiple times to calculate sigmaS
		for(j = 0; j < times; j++) {
			double t = first(N);
			// dynamic calculate avgs w/o extra memory usage
			avg += t;
			avgsqr += t*t;
		}
		avg /= N;
		avgsqr /= N;
		double sigmaS = sqrt(avgsqr - avg * avg);
		printf("sigmaS: %lf\n", sigmaS);

	}
	// calculate to see results
	for(i = 3; i <= 8; i++) {
		printf("N: %e, Result: %lf\n", pow(10, i), first(pow(10, i)));
	}
	// calculate to see results
	 printf("Multile-dimensions\n");
	for(i = 3; i <= 8; i++) {
		printf("N: %e, Result: %lf\n", pow(10, i), second(pow(10, i)));
	}
	return 0;
}
