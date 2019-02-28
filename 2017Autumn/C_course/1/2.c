#include <stdio.h>
#include <math.h>

int main()
{
	double r, h;
	printf("Enter R and H:");
	scanf("%lf%lf", &r, &h);
	printf("volume is %f\n", 3.14159 * r * r * h);
	return 0;
}
