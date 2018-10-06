/*
 * =====================================================================================
 *
 *       Filename:  3.c
 *
 *    Description:  c practice 3 code 3
 *
 *        Version:  1.0
 *        Created:  10/17/2017 07:03:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

int main()
{
	double x, fx;
	printf("please input x:");
	scanf("%lf", &x);
	if(x < 0 && x != 3)
		fx = x * x + x - 6;
	else if(x >= 0 && x < 10 && x != 2 && x != 3)
		fx = x * x - 5 * x + 6;
	else
		fx = x * x - x - 1;
	printf("x = %lf, f(x) = %lf\n", x, fx);
	return 0;
}
