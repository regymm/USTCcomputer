/*
 * =====================================================================================
 *
 *       Filename:  w.c
 *
 *    Description:  write test
 *
 *        Version:  1.0
 *        Created:  11/24/2017 10:46:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
	write(1, "hello", 5);
	write(1, "\033[37m", 5);
	write(1, "hello", 5);
	write(1, "\033[0m", 5);
	return 0;
}
