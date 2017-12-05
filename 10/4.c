/*
 * =====================================================================================
 *
 *       Filename:  4.c
 *
 *    Description:  USTC 10, 4, last
 *
 *        Version:  1.0
 *        Created:  12/05/2017 07:05:23 PM
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
	FILE *fin, *fout;
	int c;
	if(!(fin = fopen("abc.txt", "r"))) return -1;
	if(!(fout = fopen("code.txt", "w"))) return -1;
	while((c = fgetc(fin)) != EOF){
		putchar(c);
		if(c >= 'a' && c <= 'z'){
			c++;
			if(c > 'z') c -= 'z' - 'a';
		}
		fputc(c, fout);
	}
	putchar('\n');
	fclose(fin);
	fclose(fout);
	return 0;
}
