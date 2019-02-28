/*
 * =====================================================================================
 *
 *       Filename:  2.c
 *
 *    Description:  USTC computer practice 4 code 2
 *
 *        Version:  1.0
 *        Created:  10/24/2017 06:41:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

int main()
{
	int character = 0;
	int space = 0;
	int tab = 0;
	int cr = 0;
	int others = 0;
	char c;
	while((c = getchar()) != EOF){
		if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
			character++;
		else if(c == ' ')
			space++;
		else if(c == '\t')
			tab++;
		else if(c == '\n')
			cr++;
		else others++;
	}
	printf("English character: %d\n", character);
	printf("space: %d\n", space);
	printf("tab: %d\n", tab);
	printf("cr: %d\n", cr);
	printf("others: %d\n", others);
	return 0;
}
