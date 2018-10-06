/*
 * =====================================================================================
 *
 *       Filename:  3.c
 *
 *    Description:  USTC 9, 3
 *
 *        Version:  1.0
 *        Created:  11/28/2017 07:41:47 PM
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

typedef struct man{
	int num;
	struct man *next;
}Man;

int main()
{
	int n, i;
	scanf("%d", &n);
	Man *head = NULL;
	Man *q = head;
	for(i = 0; i < n; i++){
		Man *p = (Man *)malloc(sizeof(Man));
		p->num = i + 1;
		if(!head){
			head = p;
			q = p;
			continue;
		}
		q->next = p;
		q = p;
	}
	q->next = head;//cycle list
	int outed = 0;
	int cnt = 1;//0(means 3) and a person out
	Man *nowman = head;
	Man *prevman = q;
	//warning that p, q, and head will all be freed in while
	while(outed != n - 1){
		if(cnt){
			nowman = nowman->next;
			prevman = prevman->next;
		}
		else{
			prevman->next = nowman->next;
			free(nowman);
			nowman = prevman->next;
			outed++;
		}
		cnt = (cnt + 1) % 3;
	}
	printf("%d\n", prevman->num);
	free(prevman);
	return 0;
}
