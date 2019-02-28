/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  USTC 2017 8, 1
 *
 *        Version:  1.0
 *        Created:  11/21/2017 06:28:51 PM
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

#define MAX 20

void udf_strcpy(const char *src, int m, char *dest)
{
	if(m > strlen(src)){
		*dest = 0;
		return;
	}
	int m0 = m;
	while((*(dest + m - m0) = *(src + m))) m++;
}

int main()
{
	char s[MAX] = "Hello World!";
	char t[MAX];
	int m;
	scanf("%d", &m);
	udf_strcpy(s, m, t);
	printf("%s\n", t);
	return 0;
}

