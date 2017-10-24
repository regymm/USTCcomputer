/*
 * =====================================================================================
 *
 *       Filename:  3.c
 *
 *    Description:  USTC computer practice 4 code 3
 *
 *        Version:  1.0
 *        Created:  10/24/2017 06:55:09 PM
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
	long long int ans = 0, tmp = 1;
	int i;
	for(i = 1; i <= 20; i++)
		ans += tmp *= i;
	printf("%lld\n", ans);
	return 0;
}
