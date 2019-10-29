/**
 * File              : hw10.c
 * License           : GPL-3.0-or-later
 * Author            : Yimin Gu <github.com/ustcpetergu>
 * Date              : 2019.10.20
 * Last Modified Date: 2019.10.21
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

// mass of the particle which doesn't matter
double m = .01;
// [-Fm,Fm] is the range of flucturation force
double Fm = 1;
// driving force strengh and frequency
double F0 = 1;
double w = M_PI_2;
// alpha the viscious coefficient
double a = 1;
// h the step length of RK method
double h = 0.01;
// N the number of steps
int N = 5e4;
// M the times of Monte Carlo
int M = 1e4;
// v0 the initial velocity
double v0 = -0;
// x0 the initial location
double x0 = 0;
// x1,x2 are the equavalence initial conditions, calculated at beginning
double x1, x2;
// array of all the v, x, and z
double* v;
double* x;
/*double* z;*/
// array of <z^2>
double* z2avg;

// random real number in [0, 1]
double randreal()
{
	return (double) rand() / (RAND_MAX);
}

// f as described in hw10.md.
// use the reset trick to randomize F
double f(double t, double v, int reset)
{
	static double F;
	if (reset) {
		F = (2 * randreal() - 1) * Fm;
		return 0.;
	}
	return F0 / m * sin(w * t) - a / m * v + F / m;
}

// the x(t) when no F is applied
double xa(double t)
{
	return -F0/m*1/(w*w+(a/m)*(a/m))*(sin(w*t)+a/(m*w)*cos(w*t))+x1+x2*exp(-a/m*t);
}

double va(double t){
	return -F0/m*1/(w*w+(a/m)*(a/m))*(w*cos(w*t)-a/(m)*sin(w*t))-a/m*x2*exp(-a/m*t);
}

void RK(int verbose)
{
	int i = 0;
	double t;
	double vt;
	double k1, k2, k3, k4;
	v[0] = v0;
	x[0] = x0;
	t = 0;
	// main simu loop
	for(i = 0; i < N; i++) {
		// randomize F
		f(0, 0, 1);
		// maybe this can reduce some memory reference?
		vt = v[i];
		if (verbose) {
			// print for debug and redirect
			printf("%lf ", x[i]);
			/*printf("%lf ", v[i]);*/
		}
		// classical RK method
		k1 = f(t         , vt              , 0);
		k2 = f(t + h / 2., vt + h / 2. * k1, 0);
		k3 = f(t + h / 2., vt + h / 2. * k2, 0);
		k4 = f(t + h     , vt + h      * k3, 0);
		v[i + 1] = vt + h / 6. * (k1 + 2*k2 + 2*k3 + k4);
		t += h;
		// Trapezoidal rule to calculate the x
		x[i + 1] = x[i] + h * (v[i] + v[i + 1]) / 2.;
		// update z2avg on the fly
		z2avg[i] += (x[i] - xa(t))*(x[i] - xa(t));
	}
	if (verbose) {
		printf("\n");
		for(i = 0; i < N; i++) {
			printf("%lf ", xa(i * h));
		}
		printf("\n");
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s z2avg|single\n", argv[0]);
		exit(-1);
	}
	srand((unsigned)time(0));
	// convert between two initial conditions
	x2 = -m/a*(v0+F0/m*1/(w*w+(a/m)*(a/m))*w);
	x1 = F0/m*1/(w*w+(a/m)*(a/m))*a/(m*w)+x0-x2;
	// initialization
	// left some extra mem is always appreciated
	v = (double*)malloc(N * sizeof(double) + 100);
	x = (double*)malloc(N * sizeof(double) + 100);
	z2avg = (double*)malloc(N * sizeof(double) + 100);
	int i;
	for(i = 0; i < N; i++) {
		z2avg[i] = 0;
	}
	if (strcmp(argv[1], "z2avg") == 0) {
		for(i = 0; i < M; i++) {
			RK(0);
		}
		for(i = 0; i < N; i++) {
			z2avg[i] /= M;
			printf("%lf ", z2avg[i]);
		}
		printf("\n");
	}
	else if (strcmp(argv[1], "single") == 0) {
		RK(1);
	}
	free(v);free(x);free(z2avg);
	return 0;
}
