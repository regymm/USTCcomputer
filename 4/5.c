/*
 * =====================================================================================
 *
 *       Filename:  5.c
 *
 *    Description:  USTC computer practice 4 code 5
 *
 *        Version:  1.0
 *        Created:  10/24/2017 07:33:37 PM
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
	int num = 7;
	int i, j;
	char indent[100];
	for(i = 0; i < num; i++){
		for(j = 0; j < fabs(num / 2 - i); j++)
			printf("  ");
		for(j = 0; j <  num - 2 * fabs(num / 2 - i); j++)
			printf("* ");
		printf("\n");
	}
	
	return 0;
}
