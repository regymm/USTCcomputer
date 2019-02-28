/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  USTC 10, 2, last
 *
 *        Version:  1.0
 *        Created:  12/05/2017 06:27:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

typedef struct {
	int id;
	char name[100];
	int score1;
	int score2;
	int score3;
	double avg;
}Stu;
int main()
{
	Stu stu[5];
	int i;
	FILE *fin;
	if(!(fin = fopen("stud_sort", "r"))) return 1;
	for(i = 0; i < 5; i++){
		fscanf(fin, "%d%s%d%d%d%lf", &stu[i].id, stu[i].name, 
				&stu[i].score1, &stu[i].score2, &stu[i].score3, &stu[i].avg);
		stu[i].avg = (stu[i].score1 + stu[i].score2 + stu[i].score3) / 3.0;
	}
	for(i = 0; i < 5; i++){
		printf("%d %s %d %d %d %lf\n", stu[i].id, stu[i].name, stu[i].score1, stu[i].score2, stu[i].score3, stu[i].avg);
	}
	fclose(fin);
	return 0;
}
