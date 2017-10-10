/*
 * =====================================================================================
 *
 *       Filename:  3.c
 *
 *    Description:  USTC computer practice 2.3
 *
 *        Version:  1.0
 *        Created:  2017年10月10日 18时56分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

int main(void)
{
	char c = getchar();
	c >= 97 && c <= 122 ? printf("%c\n", c - 32) : printf("Wrong input!\n");
	return 0;
}
