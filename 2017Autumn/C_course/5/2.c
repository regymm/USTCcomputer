/*
 * =====================================================================================
 *
 *       Filename:  2.c
 *
 *    Description:  USTC computer practice 5 code 2
 *
 *        Version:  1.0
 *        Created:  10/31/2017 06:46:50 PM
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

char name[10][5];
int score[10];
void print()
{
	int i;
	for(i = 0; i < 10; i++)
		printf("name: %s, score: %d.\n", name[i], score[i]);
}
int main(void)
{
	int i, j;
	int t;
	char tt[5];
	for(i = 0; i < 10; i++){
		scanf("%s", name[i]);
		scanf("%d", score + i);
	}
	print();
	printf("bubble sort:\n");
	for(i = 0; i < 10 - 1; i++)
		for(j = 10 - 1; j > i; j--)
			if(score[j] > score[j - 1]){
				score[j - 1] ^= score[j];
				score[j] ^= score[j - 1];
				score[j - 1] ^= score[j];
				strcpy(tt, name[j - 1]);
				strcpy(name[j - 1], name[j]);
				strcpy(name[j], tt);

			}
	print();	
	printf("selective sort:\n");
	for(i = 0; i < 10 - 1; i++){
		t = i;
		for(j = i; j < 10; j++){
			if(score[j] >= score[t]){
				t = j;
			}
		}
		if(t != i){
			score[t] ^= score[i];
			score[i] ^= score[t];
			score[t] ^= score[i];
			strcpy(tt, name[t]);
			strcpy(name[t], name[i]);
			strcpy(name[i], tt);
		}
	}
	print();	
	return 0;
}
