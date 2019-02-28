/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  USTC 9, 1
 *
 *        Version:  1.0
 *        Created:  11/28/2017 06:33:42 PM
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
#define N 100
#define MAX 100

typedef struct{
	int num;
	char name[MAX];
	char author[MAX];
	char pub[MAX];
	double price;
}Book;
//Book b[N];
int main()
{
	int n, i;
	scanf("%d", &n);
	Book *b = (Book *)malloc(n * sizeof(Book));
	for(i = 0; i < n; i++){
		scanf("%d", &b[i].num);
		scanf("%s", b[i].name);
		scanf("%s", b[i].author);
		scanf("%s", b[i].pub);
		scanf("%lf", &b[i].price);
	}
	double avg = 0;
	for(i = 0; i < n; i++)
		avg += b[i].price;
	avg /= n;
	printf("%lf\n", avg);
	free(b);
	return 0;
}
