/*
 * =====================================================================================
 *
 *       Filename:  schrage.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/12/2019 10:12:58 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (github.com/ustcpetergu), 
 *   Organization:  USTC
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Schrage moding method
int azmodm(int a, int z, int m, int q, int r)
{
	unsigned int t = a * (z % q) - r * (z / q);
	if (t < 0) t += m;
	return t;
}

// The RNG
double schrage16807()
{
	static int first = 1;
	static unsigned int I = 1;
	static unsigned int b = 0;
	// IBM randu
	/*static unsigned int a = 65539;*/
	/*static unsigned int m = 2147483648;*/
	// 16807
	static unsigned int a = 16807;
	static unsigned int m = 2147483647;
	static unsigned int q;
	static unsigned int r;
	// Calculate other parameters at the first time
	if (first) {
		first = 0;
		q = m / a;
		r = m % a;
	}
	int t = azmodm(a, I, m, q, r);
	I = (t + b) % m;
	return (double)I / m;
}

#define MAX(a,b) ((a)>(b)?(a):(b))
// OP
#define OP ^
double fibonacci()
{
	static int p = 0x5D;
	static int q = 0xAA;
	static long long int arr[500];
	// ptr means n
	static int ptr = 0;
	static int first = 1;
	int  i;
	if (first) {
		ptr = MAX(p, q);
		// initialize first ptr elements with numbers, here just use our RNG
		for(i = 0; i <= ptr; i++)
			arr[i] = schrage16807() * 2147483647;
		first = 0;
	}
	ptr = (ptr + 1) % 500;
	// update in the circular linear list
	arr[ptr] = (arr[(ptr - p + 500) % 500] OP arr[(ptr - q + 500) % 500]) % 2147483647;
	/*printf("%lld %lld %lld %d %lld \n", arr[(ptr - p + 500) % 500], arr[(ptr - q + 500) % 500], (arr[(ptr - p + 500) % 500] OP arr[(ptr - q + 500) % 500]) % 2147483647, ptr, arr[ptr]);*/
	return arr[ptr] / (double)2147483647;
}

int main() {
	int i;
	int N = 2E7;
	// Task 1: print N random numbers into file and use the plot.py to plot
	// gcc schrage.c -lm && ./a.out > data.txt && python3 plot.py
	/*for(i = 0; i < N; i++)*/
		/*printf("%lf ", schrage16807());*/
	double* arr = (double*)malloc(N * sizeof(double));
	// Task 2: average of x^k and C(l)
	// The array of random numbers
	for(i = 0; i < N; i++)
		arr[i] = schrage16807();
	// Also see the performance of standard generator rand()
	/*for(i = 0; i < N; i++)*/
		/*arr[i] = (double)rand()/RAND_MAX;*/
	int k;
	double avgs[100];
	for(k = 1; k < 5; k++) {
		double avg = 0;
		for(i = 0; i < N; i++) {
			avg += pow(arr[i], k);
		}
		avg /= N;
		avgs[k] = avg;
		// calculated avg
		printf("k=%d avg(x^k)=%lf\n", k, avg);
	}
	int l;
	for(l = 1; l < 20; l++) {
		double avgxlx = 0;
		for(i = 0; i < N - l; i++)
			avgxlx += arr[i] * arr[i + l];
		// Calculate <x_{k+l}x_k>
		avgxlx /= N - l;
		// Calculate the C(l)
		double Cl = (avgxlx - pow(avgs[1], 2) ) / (avgs[2] - pow(avgs[1], 2));
		printf("C(%d)=%lf\n", l, Cl);
	}
	// Task 3: compare 16807 and Fibonacci
	int cnt16807 = 0;
	int cntfibo = 0;
	// count the numbers of pairs that satisfy the relation
	for(i = 1; i < N - 1; i++)
		if((arr[i - 1] < arr[i + 1]) && (arr[i + 1] < arr[i]))
			cnt16807++;
	// result
	printf("%lf\n", cnt16807 / (double)N);
	// fibonacci
	for(i = 0; i < N; i++)
		arr[i] = fibonacci();
	for(i = 1; i < N - 1; i++)
		if((arr[i - 1] < arr[i + 1]) && (arr[i + 1] < arr[i]))
			cntfibo++;
	printf("%lf\n", cntfibo / (double)N);
	free(arr);
	return 0;
}
