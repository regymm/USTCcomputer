/*
 * =====================================================================================
 *
 *       Filename:  3.c
 *
 *    Description:  USTC computer practice 6 code 3
 *
 *        Version:  1.0
 *        Created:  11/07/2017 07:07:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

static void realint2str(char *s, int n, int len)
{
	if(!len){
		s[0] = '\0';
		return;
	}
	int i;
	int pow = 1;
	for(i = 1; i < len; i++) pow *= 10;
	s[0] = n / pow + 48;
	realint2str(s + 1, n % pow, len - 1);
}
void int2str(char *s, int n)
{
	if(n < 0){
		s[0] = '-';
		int2str(s + 1, -n);
		return;
	}
	int pow = 1;
	int len = 0;
	while(n / pow > 10){
		pow *= 10;
		len++;
	}
	len++;
	realint2str(s, n, len);
}
int main()
{
	int n;
	printf("Enter integer n:");
	scanf("%d", &n);
	char s[11];
	int2str(s, n);
	printf("%s\n", s);
	return 0;
}
