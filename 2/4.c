/*
 * =====================================================================================
 *
 *       Filename:  4.c
 *
 *    Description:  USTC computer practice 2.4
 *
 *        Version:  1.0
 *        Created:  2017年10月10日 19时00分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <math.h>
#define pi (3.141593)

int main(void)
{
	double r, h, s;
	scanf("%lf%lf", &r, &h);
	printf("%.2lf\n%.2lf\n%.2lf\n", 2 * pi * r, s = pi * r * r, pi * r * sqrt(r * r + h * h));
	printf("%.2lf\n", s * h / 3.0);
	return 0;
}
