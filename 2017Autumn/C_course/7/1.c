/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  USTC 7, 1
 *
 *        Version:  1.0
 *        Created:  11/14/2017 06:30:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

#define N 100

void select(int *a, int n)
{
	int i, j;
	for(i = 0; i < n - 1; i++){
		int k = i;
		for(j = i + 1; j < n; j++){
			if(*(a + j) > *(a + k)){
//				k ^= *(a + j);
//				*(a + j) ^= k;
//				k ^= *(a + j);
				k = j;
			}
		}
		if(k != i){
			*(a + i) ^= *(a + k);
			*(a + k) ^= *(a + i);
			*(a + i) ^= *(a + k);
		}
	}
}
int main()
{
	int a[N];
	int i;
	int n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", a + i);
	select(a, n);
	for(i = 0; i < n; i++)
		printf("%d, ", a[i]);
	printf("\n");
	return 0;
}
