/*
 * =====================================================================================
 *
 *       Filename:  5.c
 *
 *    Description:  c practice 3 code 5
 *
 *        Version:  1.0
 *        Created:  10/17/2017 07:29:30 PM
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
	char c;
	scanf("%c", &c);
	if(c <= 'z' && c >= 'a'){
		c -= 32;
		printf("change to upper:%c\n", c);
	}
	switch(c){
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
		case 'A':
		case 'E':
		case 'I':
		case 'O':
		case 'U': printf("Yes\n");break;
		default: printf("No\n");
	}
	printf("Upper ascii:%d, lower ascii:%d\n", c, c + 32);
	return 0;
}
