/**
 * File              : hw7.c
 * License           : GPL-3.0-or-later
 * Author            : Yimin Gu <github.com/ustcpetergu>
 * Date              : 2019.10.01
 * Last Modified Date: 2019.10.01
 * ---
 * Computational physics homework 7, similar to 6
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int p_x[10000];
int p_p[10000];
int p_real[10000];

void readdata()
{
	// read the data.TXT, input provided by redirecting
	scanf("%*s %*s\n");
	int i = 0, j = 0;
	while(scanf("%d %d", p_x + i, p_p + i) == 2)
		i++;
	// use a method similar to hash, because x provided in the file is all continuous
	for(j = 0; j < i; j++)
		p_real[p_x[j]] = p_p[j];
	double intt = 0;
	for(j = 0; j < i - 1; j++)
		intt += (p_p[j] + p_p[j + 1]) / 2.;
	fprintf(stderr, "Integral: %lf\n", intt);
	/*for(i = 2900; i < 3200; i++)*/
		/*printf("%d\n", p_real[i]);*/
}

// p(x), the target, discrete values to be continue-fied
double p(double x)
{
	if (x < 2900 || x > 3013) {
		printf("%lf out of range in p\n", x);
		exit(-1);
	}
	int xint = (int) (x);
	// avoid potential round error due to FP precision
	if (xint < 2900) xint = 2900;
	if (xint > 3013) xint = 3013;
	return p_real[xint] + (p_real[xint + 1] - p_real[xint]) * (x - (double)xint);
}

// F(x), the segmentation func. 
double F(double x)
{
	if (2900 < x && x <= 2994)
		return 5672;
	else if (2994 < x && x <= 3013)
		return 35560;
	else
		return 0;
}

// G the reverse of the calculus of F
double G(double x)
{
	if (0 <= x && x <= 533168)
		return ((2994 - 2900) / (double) 533168) * x + 2900;
	else if (533168 < x && x <= 1208808)
		return ((3013 - 2994) / (double) (1208808 - 533168)) * (x - 533168) + 2994;
	else {
		printf("%lf out of range in G\n", x);
		exit(-1);
	}
}

// random real number in [0, 1]
double randreal()
{
	return (double) rand() / (RAND_MAX);
}

// simple 
double get1()
{
	double p1 = randreal() * (3013 - 2900) + 2900;
	double p2 = randreal() * 35560;
	if(p2 < p(p1))
		return p1;
	else
		return 9999;


}

// advanced
double get2()
{
	double p1 = randreal() * 1208808;
	double x0 = G(p1);
	double p2 = randreal() * F(x0);
	if(p2 < p(x0))
		return x0;
	else
		return 9999;
}

int main(int argc, char* argv[])
{
	/*printf("%lf\n", G(0));*/
	/*printf("%lf\n", G(10000));*/
	/*printf("%lf\n", G(533168));*/
	/*printf("%lf\n", G(1208807));*/
	readdata();
	srand((unsigned)time(0));
	int i;
	int N = 3000000;
	int cnt = 0;
	double t;
	if(argc != 2) {
		fprintf(stderr, "%s (task1|task2)\n", argv[0]);
		exit(-2);
	}
	else if (strcmp(argv[1], "task1") == 0) {
		// task1: 简单抽样
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
		// task2: 舍选法抽样
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

