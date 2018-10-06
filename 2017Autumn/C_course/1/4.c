#include <stdio.h>
#include <math.h>

int main()
{
	int a, b, c;
	printf("Enter a b c:");
	scanf("%d%d%d", &a, &b, &c);
	if ( a + b > c && a + c > b && b + c > a ){
		double p = .5 * ( a + b + c );
		printf("can\narea is %f\n",sqrt(p * (p - a) * (p - b) * (p - c)));
	}
	else printf("cant\n");
	return 0;
}
