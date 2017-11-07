/*
 * =====================================================================================
 *
 *       Filename:  4.c
 *
 *    Description:  USTC computer practice 6 code 4
 *
 *        Version:  1.0
 *        Created:  11/07/2017 07:40:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

#define myswap(a, b) do{\
		*a ^= *b;\
		*b ^= *a;\
		*a ^= *b;\
	}while(0)
int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	myswap(&a, &b);
	printf("%d %d\n", a, b);
	return 0;
}

