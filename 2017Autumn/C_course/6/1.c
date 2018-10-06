/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  USTC computer practice 6 code 1
 *
 *        Version:  1.0
 *        Created:  11/07/2017 06:31:42 PM
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

void count(char s[])
{
	int i = 0;
	int letter = 0, num = 0, space = 0, others = 0;
	while(s[i]){
		if(s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z')
			letter++;
		else if(s[i] >= '0' && s[i] <= '9')
			num++;
		else if(s[i] == ' ')
			space++;
		else others++;
		i++;
	}
	printf("letter: %d, num: %d, space: %d, others:%d\n", 
			letter, num, space, others);
}

int main()
{
	char s1[] = "123 CBA 456 def";
	char s2[] = "Hello world! Hello 2017!";
	char s3[] = "!@#$& 147 258 QwQ";
	char s4[100];
	printf("Enter a string (< 100):");
	fgets(s4, 99, stdin);
	s4[strlen(s4) - 1] = '\0';// ignore the last \n read in stdin
	count(s1);
	count(s2);
	count(s3);
	count(s4);
	return 0;
}
