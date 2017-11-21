/*
 * =====================================================================================
 *
 *       Filename:  ws.c
 *
 *    Description:  winsize test
 *
 *        Version:  1.0
 *        Created:  11/19/2017 04:21:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <sys/ioctl.h>

int main()
{
	struct winsize size;
	if(ioctl(1, TIOCGWINSZ, &size) < 0){
		printf("failed\n");
	}
	printf("row: %d, col: %d\n", size.ws_row, size.ws_col);
	return 0;
}
