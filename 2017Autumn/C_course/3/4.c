/*
 * =====================================================================================
 *
 *       Filename:  4.c
 *
 *    Description:  c practice 3 code 4
 *
 *        Version:  1.0
 *        Created:  10/17/2017 07:11:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int score;
	printf("please enter score:");
	scanf("%d", &score);
	if(score < 0 || score > 100){
		printf("illegal input!\n");
		exit(1);
	}
	printf("You score is %d, ", score);
	switch(score / 10){
	case 10:
	case 9: printf("grade is A\n");break;
	case 8: printf("grade is B\n");break;
	case 7: printf("grade is C\n");break;
	case 6: printf("grade is D\n");break;
	default: printf("grade is E\n");break;  
	}
}
