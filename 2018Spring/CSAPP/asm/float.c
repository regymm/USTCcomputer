#include <stdio.h>
double adddouble(double a, double *b, int c)
{
	double ans = a + *b;
	double ans2 = a + c;
	printf("%lf", ans2);
	return ans;
}
