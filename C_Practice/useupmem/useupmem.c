/*
 * =====================================================================================
 *
 *       Filename:  useupmem.c
 *
 *    Description:  my practice for book Linux C, use up memory
 *
 *        Version:  1.0
 *        Created:  2017年10月06日 15时45分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

// Warning: this program will try to use up memory!

#include <stdlib.h>
#include <stdio.h>

#define MAX 1000000000
int main()
{
	int i,all = 0;
	int *p;
	for(i = 0; i < MAX; i++){
		if(p = (int *)malloc(1024 * 1024 * 1024))
			printf("1G memory used\ntotal %dG\n", all = all + 1);
		else printf("failed after %dG used\n", all);
	}
	return 0;
}

