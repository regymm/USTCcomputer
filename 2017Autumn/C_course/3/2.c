/*
 * =====================================================================================
 *
 *       Filename:  2.c
 *
 *    Description:  c practice 3 code 2
 *
 *        Version:  1.0
 *        Created:  10/17/2017 06:45:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

int judge_positive(double x)
{
	return x >= 0 ? 1 : 0;
}
int main()
{
	double x;
	scanf("%lf", &x);
	x -= 3000;
	printf("tax is %lf\n",
	(judge_positive(x - 5000)) * x * .25 + 
	!(judge_positive(x - 5000)) * (judge_positive(x - 3000)) * x * .20 +
	!(judge_positive(x - 3000)) * (judge_positive(x - 1500)) * x * .15 +
	!(judge_positive(x - 1500)) * (judge_positive(x - 500)) * x * .10 +
	!(judge_positive(x - 500)) * judge_positive(x) * x * .05);
	return 0;
}
