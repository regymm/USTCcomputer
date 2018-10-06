/*
 * =====================================================================================
 *
 *       Filename:  4.c
 *
 *    Description:  USTC computer practice 4 code 4
 *
 *        Version:  1.0
 *        Created:  10/24/2017 07:03:03 PM
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

int judge(int x)
{
	int i;
	if(x < 2) return 0;
	for(i = 2; i <= sqrt(x); i++)
		if(x % i == 0)
			return 0;
	return 1;
}
int main(void)
{
	int i, cnt = 0, sum = 0;
	printf("input the 10 biggest prime number less than 500 and their sum:\n");
	for(i = 499; i > 1, cnt < 10; i -= 2){
		if(judge(i)){
			cnt++;
			sum+=i;
			printf("%d ", i);
			if(cnt != 10) printf("+ ");
		}
	}
	if(cnt + 1 < 10)//including unjudged number 2
		printf("NO ENOUGH PRIMES!\n");
	else printf(" = %d\n", sum);
	return 0;
}
