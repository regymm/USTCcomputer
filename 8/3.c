/*
 * =====================================================================================
 *
 *       Filename:  3.c
 *
 *    Description:  USTC 2017 8, 3
 *
 *        Version:  1.0
 *        Created:  11/21/2017 06:48:55 PM
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
	int n, i, outed = 0, flag = -1;
	int *p;
	scanf("%d", &n);
	printf("All %d persons...\n", n);
	p = (int *)malloc(n * sizeof(int));
	for(i = 0; i < n; i++)
		*(p + i) = 1;
	i = 1;
	while(outed < n - 1){
		flag = (flag + 1) % n;
		if(!*(p + flag)){
			continue;
		}
		if(i == 0){
			printf("out: %d\n", flag + 1);
			*(p + flag) = 0;
			outed++;
		}
		i = (i + 1) % 3;
	}
	while(!*(p + flag)){
		flag = (flag + 1) % n;
	}
	printf("survivor: %d\n", flag + 1);
	free(p);
	return 0;
}
