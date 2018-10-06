/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  mini ACM on nowcoder.com, USTC
 *
 *        Version:  1.0
 *        Created:  12/03/2017 01:55:09 PM
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

#define MAX 1000
int main()
{
	char s[MAX];
	int hash[MAX];
	while(fgets(s, MAX, stdin)){
		int len = strlen(s);
		int i;
		for(i = 0; i < MAX; i++)
			hash[i] = 0;
		for(i = 0; i < len; i++){
			hash[(int)s[i]]++;
		}
		int flag = 0;
		for(i = 0; i < len && flag == 0; i++)
			if(s[i] != '\n' && hash[(int)s[i]] == 1){
				printf("%c\n", s[i]);
				flag = 1;
			}
		if(flag == 0) printf("-1\n");
	}
	return 0;
}
