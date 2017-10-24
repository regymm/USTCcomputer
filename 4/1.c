/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  USTC computer practice 4 code 1
 *
 *        Version:  1.0
 *        Created:  10/24/2017 06:29:28 PM
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
#include <math.h>

int main()
{
	char id[100];
	double score1, score2, score3;
	char idmax[50][100], idmin[50][100];
	double scoremax = -1, scoremin = 1000;
	int flagmax = 0, flagmin = 0;
	double scoreavg;
	int i;
	for(i = 1; i <= 5; i++){
		printf("%d:input the student id and 3 scores:\n", i);
		scanf("%s", id);
		scanf("%lf%lf%lf", &score1, &score2, &score3);
		scoreavg = (score1 + score2 + score3) / 3.0;
		printf("student id %s: average score %lf\n", id, scoreavg);
		if(scoreavg > scoremax){
			scoremax = scoreavg;
			strcpy(idmax[0], id);
			flagmax = 0;
		}
		else if((scoreavg - scoremax) < 1e-4){
			flagmax++;
			strcpy(idmax[flagmax], id);
		}
		if(scoreavg < scoremin){
			scoremin = scoreavg;
			strcpy(idmin[0], id);
			flagmin = 0;
		}
		else if((scoreavg - scoremin) < 1e-4){
			flagmin++;
			strcpy(idmin[flagmin], id);
		}
//		printf("%lf, %lf\n", scoremax, scoremin);
//		printf("%d, %d\n", flagmax, flagmin);
	}
	for(i = 0; i <= flagmax; i++) 
		printf("max: student id %s, score %lf\n", idmax[i], scoremax);
	for(i = 0; i <= flagmin; i++) 
		printf("min: student id %s, score %lf\n", idmin[i], scoremin);
	return 0;
}
