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
#include <string.h>

#define myswap(a, b) do{\
		a ^= b;\
		b ^= a;\
		a ^= b;\
	}while(0)

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
	int i, j;
	FILE *fin, *fout;
	if(!(fin = fopen("stud_dat", "r"))) return 1;
	for(i = 0; i < 5; i++){
		fscanf(fin, "%d%s%d%d%d%lf", &stu[i].id, stu[i].name, 
				&stu[i].score1, &stu[i].score2, &stu[i].score3, &stu[i].avg);
		stu[i].avg = (stu[i].score1 + stu[i].score2 + stu[i].score3) / 3.0;
	}
	char t[100];
	double tmp;
	for(i = 0; i < 5 - 1; i++){
		for(j = i; j < 5; j++)
			if(stu[j].avg < stu[j - 1].avg){
				myswap(stu[j].id, stu[j - 1].id);
				myswap(stu[j].score1, stu[j - 1].score1);
				myswap(stu[j].score2, stu[j - 1].score2);
				myswap(stu[j].score3, stu[j - 1].score3);
				strcpy(t, stu[j].name);
				strcpy(stu[j].name, stu[j - 1].name);
				strcpy(stu[j - 1].name, t);
				tmp = stu[j].avg;
				stu[j].avg = stu[j - 1].avg;
				stu[j - 1].avg = tmp;
			}
	}
	if(!(fout = fopen("stud_sort", "w"))) return 1;
	for(i = 0; i < 5; i++){
		fprintf(fout, "%d %s %d %d %d %lf\n", stu[i].id, stu[i].name, stu[i].score1, stu[i].score2, stu[i].score3, stu[i].avg);
	}
	fclose(fin);
	fclose(fout);
	fclose(fin);
}
