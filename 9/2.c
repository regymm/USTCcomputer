/*
 * =====================================================================================
 *
 *       Filename:  2.c
 *
 *    Description:  USTC 9, 2
 *
 *        Version:  1.0
 *        Created:  11/28/2017 06:54:42 PM
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

#define N 100

typedef struct{
	int num;
	char name[10];
	char sex;
	int age;
	double score;
}Stu;

int input(Stu **stu)
{
	int n, i;
	scanf("%d", &n);
	for(i = 0; i < n; i++){
		scanf("%d %s %c %d %lf", &stu[i]->num , stu[i]->name, &stu[i]->sex, &stu[i]->age, &stu[i]->score);
	}
	return n;
}
void print(Stu **stu, int n){
	int i;
	for(i = 0; i < n; i++){
		printf("%d ", stu[i]->num);
		printf("%s ", stu[i]->name);
		printf("%c ", stu[i]->sex);
		printf("%d ", stu[i]->age);
		printf("%.1lf", stu[i]->score);
		printf("\n");
	}
}
void bubblesort(Stu **stu, int n)
{
	int i, j;
	Stu *t;
	for(i = 0; i < n - 1; i++){
		for(j = n - 1; j > i; j--){
			if(stu[j - 1]->score > stu[j]->score){
				t = stu[i];
				stu[i] = stu[j];
				stu[j] = t;
			}
		}
	}
}
void selectsort(Stu **stu, int n){
	int i, j, t;
	for(i = 0; i < n - 1; i++){
		t = i;
		for(j = i; j < n; j++)
			if(stu[j]->score < stu[t]->score)
				t = j;
		if(t != i){
			Stu *tmp = stu[i];
			stu[i] = stu[t];
			stu[t] = tmp;
		}
	}
}

int main(){
	int n, i;
	Stu stu[N];
	Stu *pstu[N];
	Stu **ppstu = pstu;
	for(i = 0; i < N; i++)
		pstu[i] = stu + i;
	n = input(ppstu);
	print(ppstu,  n);
	printf("Bubblesort:\n");
	bubblesort(ppstu, n);
	print(ppstu,  n);
	for(i = 0; i < N; i++)
		pstu[i] = stu + i;
	printf("Selectsort:\n");
	selectsort(ppstu, n);
	print(ppstu,  n);
	return 0;
}
