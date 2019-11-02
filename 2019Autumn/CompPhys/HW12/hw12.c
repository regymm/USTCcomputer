/**
 * File              : hw12.c
 * License           : GPL-3.0-or-later
 * Author            : Yimin Gu <github.com/ustcpetergu>
 * Date              : 2019.10.29
 * Last Modified Date: 2019.10.29
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


// the main simulation
// iteration function: x_{n+1} = R sin(Pi x_n)
void simu()
{
	// range and step of lambda
	double Rmin = 1.;
	double Rmax = 4.;
	double Rstep = 1e-3;
	double R;
	// ignored and taken points
	double pntskip = 900;
	double pnttake = 400;
	double pntall = pnttake + pntskip;
	// initial value of x
	double xinit = 0.4;
	double x;
	int i, j;
	// main iteration, print used points
	R = Rmin;
	while(R < Rmax) {
		printf("%lf ", R);
		x = xinit;
		for(i = 0; i < pntskip; i++) {
			x = R * sin(x);
		}
		for(; i < pntall; i++) {
			x = R * sin(x);
			printf("%lf ", x);
		}
		printf("\n");
		R += Rstep;
	}
}

// redirect the output to data.txt and use Matlab to plot
int main(int argc, char* argv[])
{
	simu();
	return 0;
}
