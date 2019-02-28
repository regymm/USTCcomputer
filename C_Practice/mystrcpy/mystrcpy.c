/*
 * =====================================================================================
 *
 *       Filename:  mystrcpy.c
 *
 *    Description:  my str practice of book Linux C
 *
 *        Version:  1.0
 *        Created:  2017/10/06 12:31:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

char* mystrcpy(char* dest, const char* src)
{
	size_t i = 0;
	while(dest[i] = src[i]) i++;
	return dest;
}

char *shrink_space(char *dest, const char *src, size_t n)
{
	int i = -1, j = 0;
	while(src[++i] && j < n) 
		if(src[i] == '\n' || src[i] == '\t' || src[i] == '\r' || src[i] == ' '){
				if(j - 1 == -1 || dest[j - 1] != ' ') dest[j++] = ' ';
			}
		else dest[j++] = src[i];
	dest[j] = '\0';
	return dest;
}


int main()
{
	char a[50] = "Hello,world!";
	char b[50];
	mystrcpy(b, a);
	printf("%s\n", b);
	char c[100] = "   \t\tasd\n\n\tasd\t\r\n   asdfdsa\n\tasd";
	char d[20];
	printf("from:%s\nto:%s\n", c, shrink_space(d, c, 20));
	return 0;
}
