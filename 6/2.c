/*
 * =====================================================================================
 *
 *       Filename:  2.c
 *
 *    Description:  USTC computer practice 6 code 2
 *
 *        Version:  1.0
 *        Created:  11/07/2017 06:46:05 PM
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
#include <string.h>
#define N 10000000
int prime[N] = {0};
void getprime()
{
	memset(prime, 1, N);
	//note that prime[i] maybe not 1, but they are
	//not 0, and that's ok
	int i = 2;
	int j;
	while(i < sqrt(N)){
		j = 2 * i;
		while(j < N){
			prime[j] = 0;
			j += i;
		}
		i++;
		while(prime[i] == 0)
			i++;
	}
}
int main()
{
	int n;
	printf("Enter n(even, >=6, <=10e+7):");
	scanf("%d", &n);
	if(n < 6 || n % 2 != 0){
		printf("Wrong input!\n");
		return 1;
	}
	getprime();
	int i;
	for(i = 2; i < (n + 1) / 2; i++){
		if(prime[i])
			if(prime[n - i])
				printf("%d = %d + %d\n", n, i, n - i);
	}
	return 0;
}
