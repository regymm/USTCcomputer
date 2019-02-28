/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  c practice 3 code 1
 *
 *        Version:  1.0
 *        Created:  10/17/2017 06:23:05 PM
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

int main()
{
	double a, b, c;
	int flag = 0;
	scanf("%lf%lf%lf", &a, &b, &c);
	if(a + b > c && a + c > b && b + c > a){
		if(a == b && b == c){
			printf("equilateral triangle\n");
		}
		else{
			if(fabs((a - b) * (b - c) * (c - a)) < 1e-6){
				printf("isosceles triangle\n");
				flag = 1;
			}
			if(fabs((a * a + b * b - c * c) * (a * a + c * c - b * b) *
			(b * b + c * c - a * a)) < 1e-6){
				printf("right-angled triangle\n");
				flag = 1;
			}
			if(!flag){
				printf("ordinary triangle\n");
			}
		}
		printf("area is %lf\n", sqrt((a + b + c) * (a + b - c) * (c + b - a)
		 * (a + c - b) / 16));
	}
	else{
		printf("DATA ERROR!\n");
	}
	return 0;
}

