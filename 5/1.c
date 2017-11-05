/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  USTC computer practice 5 code 1
 *
 *        Version:  1.0
 *        Created:  10/31/2017 06:26:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#define MAX ((1 << 31) - 1)

int main(void)
{
	int a[20] = {3, 5, 7, 9, 11, 13, 17, 19, 21, 23};
	int b[10] = {4, 8, 9, 10, 24, 1, 8, 18, 9, 10};
	int i, j, k, ii;
	for(i = 10; i < 20; i++) a[i] = MAX;
	for(i = 0; i < 10; i++){
		j = 0;
		while(a[j] < b[i]) j++;
//		printf("%d\n", j);
//		printf("%d,\n", b[i]);
//		for(ii = 0; ii < 20; ii++)
//			printf("%d ", a[ii]);
//		printf("\n");
		for(k = i + 10; k > j; k--)
			a[k] = a[k - 1];
		a[j] = b[i];
	}
	for(i = 0; i < 20; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}

