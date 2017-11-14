/*
 * =====================================================================================
 *
 *       Filename:  3.c
 *
 *    Description:  USTC 7, 3
 *
 *        Version:  1.0
 *        Created:  11/14/2017 06:57:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>

int *count(char *s){
	static int a[]={0, 0, 0, 0, 0};
	int i;
	for(i = 0; i < 4; i++)
		*(a + i) = 0;
	int len = 0;
	while(*(s + len)){
		if(*(s + len) >= 'A' && *(s + len) <= 'Z')
			(*a)++;
		else if(*(s + len) >= 'a' && *(s + len) <= 'z')
			(*(a + 1))++;
		else if(*(s + len) == ' ')
			(*(a + 2))++;
		else if(*(s + len) >= '0' && *(s + len) <= '9')
			(*(a + 3))++;
		else (*(a + 4))++;
		len++;
	}
	return a;
}
int main()
{
	char s[100];
	fgets(s, 100, stdin);
	*(s + strlen(s) - 1) = 0;
	int *ans = count(s);
	printf("upper: %d, lower: %d, space: %d, num: %d, others: %d\n", 
			ans[0], ans[1], ans[2], ans[3], ans[4]);
	return 0;
}

