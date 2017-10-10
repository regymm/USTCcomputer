/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  USTC computer practice 2.1
 *
 *        Version:  1.0
 *        Created:  2017年10月10日 18时39分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

int main(void)
{
	int a, b;
	printf("%f\n", 3.5 + 1/2 + 56%10);
	a = 2;
	printf("%d\n", (a++ * 1/3));
	float x = 2.5;
	a = 7;
	float y = 4.7;
	printf("%f\n", x + a%3 * (int)(x + y) % 2/4);
	a = 2; b = 3; x = 3.5; y = 2.5;
	printf("%f\n", (float)(a + b) / 2 + (int)x % (int)y);
	x = 3; y = 4;
	printf("%f\n", x = (x = ++y, x + 5, x / 5));
	x = 4; y = 3;
	printf("%d\n", (x >= y >= 2) ? 1 : 0);
	return 0;
}
