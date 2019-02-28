/*
 * =====================================================================================
 *
 *       Filename:  2.c
 *
 *    Description: USTC computer practice 2.2 
 *
 *        Version:  1.0
 *        Created:  2017年10月10日 18时52分10秒
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
	int a = 3, b = 4, c = 5;
	int x, y;
	printf("%d\n", b > c && b == c);
	printf("%d\n", !(a > b) && !c || 1);
	printf("%d\n", !(x = a) && (y = b) && 0);
	printf("%d\n", !(a + b) + c - 1 && b + c / 2);
	return 0;
}
