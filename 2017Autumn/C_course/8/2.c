/*
 * =====================================================================================
 *
 *       Filename:  2.c
 *
 *    Description:  USTC 2017 8, 2
 *
 *        Version:  1.0
 *        Created:  11/21/2017 06:43:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int dim;
	scanf("%d", &dim);
	int *a, *b;
	a = (int *)malloc(dim * sizeof(int));
	b = (int *)malloc(dim * sizeof(int));
	int i;
	for(i = 0; i < dim; i++)
		scanf("%d", a + i);
	for(i = 0; i < dim; i++)
		scanf("%d", b + i);
	int sum = 0;
	for(i = 0; i < dim; i++)
		sum += *(a + i) * *(b + i);
	printf("%d\n", sum);
	free(a);
	free(b);
	return 0;
}
