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

#define MAX 10000
int mystack[MAX] = {-1, 0};
int num = 0;
int in[MAX] = {0};
int out[MAX] = {0};
int main()
{
	int buf[MAX];
	int i = 0;
	int len = 0;
	while(scanf("%d", buf + i) == 1){
		i++;
		len++;
	}
	len /= 2;
	for(i = 0; i < len; i++)
		in[i] = buf[i];
	for(; i < len * 2; i++)
		out[i - len] = buf[i];
//	for(i = 0; i < len; i++)
//		printf("%d,", in[i]);
//	for(i = 0; i < len; i++)
//		printf("%d,", out[i]);
	int iin = 0;
	int iout = 0;
	while(iin <= len){
		if(in[iin] == out[iout]){
			iin++;iout++;
			continue;//ok
		}
		if(out[iout] == mystack[num]){
			if(num == 0){
				printf("0");
				return 0;//empty, failed
			}
			//pop mystack
			iout++;
			num--;
			continue;
		}
		num++;
		mystack[num] = in[iin];
		iin++;
		//push mystack
	}
	if(mystack[num] != -1)
		printf("0");//fail
	else
		printf("1");//ok
	return 0;
}
