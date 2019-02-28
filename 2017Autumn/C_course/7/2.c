/*
 * =====================================================================================
 *
 *       Filename:  2.c
 *
 *    Description:  USTC 7, 2
 *
 *        Version:  1.0
 *        Created:  11/14/2017 06:44:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

int udf_strlen(char *s)
{
	int len = 0;
	while(*(s + len)) len++;
	return len;
}
int main()
{
	char s[100] = "Hello world! Hello 2017!";
//	fgets(s, 100, stdin);
	printf("length is %d.\n", udf_strlen(s));
	return 0;
}
