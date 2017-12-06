/*
 * =====================================================================================
 *
 *       Filename:  GameofLife.c
 *
 *    Description:  USTC computer project Game of Life, 2017, teacher Liu Yong
 *
 *        Version:  1.0
 *        Created:  12/05/2017 08:09:02 PM
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
#include <string.h>
#include <time.h>
#include "GoL.h"

void game()
{
	if(!(map = (Cell **)malloc(ALL * sizeof(Cell)))){
		printf("Out of memory!\n");
		exit(1);
	}
	randomize();
	updatearound();
	char c;
	int isgame = 1;
	clearscreen();
	while(isgame){
		updatescreen();
		updatecell();
		updatearound();
		c = getchar();
		if(c == 'q')
			isgame = 0;
	}
}
void randomize()
{
	int i, j;
	int random;
	for(i = 0; i < COL; i++)
		for(j = 0; j < ROW; j++){
			random = rand();
			map[i][j].alive = 
				(random / 65535.0 < PERCENT / 100.0) ? 1 : 0;
		}
}
void updatearound()
{
	int i, j, k;
	int around;
	int dx[] = {1, 1, 1, -1, -1, -1, 0, 0};
	int dy[] = {1, 0,-1,  1,  0, -1,-1, 1};
	for(i = 0; i < COL; i++)
		for(j = 0; j < ROW; j++){
			map[i][j].neighbour = 0;
			for(k = 0; k < 8; k++){
				if(CIRCLE)//circle mode
				map[i][j].neighbour += 
				map[(i + dx[k] + COL) % COL][(j + dy[k] + ROW) % ROW].alive;
				else//border mode
					if(i + dx[k] > 0 && i + dx[k] <= COL && 
							j + dy[k] > 0 && j + dy[k] <= ROW)
						map[i][j].neighbour += 
							map[i + dx[k]][j + dy[k]].alive;
			}
		}
}
void updatecell()
{
	int i, j, k;
	int changeflag = 0;
	for(i = 0; i < COL; i++)
		for(j = 0; j < ROW; j++){
			k = 0;
			//come alive
			while(CELL_ALIVE_NUM[k] != -1){
				if(map[i][j].neighbour == CELL_ALIVE_NUM[k]){
					map[i][j].alive = 1;
					changeflag = 1;
				}
				k++;
			}
			k = 0;
			//keep alive
			while(CELL_KEEP_NUM[k] != -1){
				if(map[i][j].alive == 1 && 
						map[i][j].neighbour == CELL_KEEP_NUM[k])
					changeflag = 1;
				k++;
			}
			//other cases, change to or remain die
			if(changeflag == 0)
				map[i][j].alive = 0;
		}
}
void start()
{
	srand((unsigned)time(0));
	welcome();
	config();
}
void end()
{
	free(map);
	printf("Goodbye!\n");
}
void config()
{
	int flag;
	char buf[BUFSIZE];
	int tmp;
	printf("config parameters...\n");
	printf("press Enter to use default value in []\n");
	//a very complex(verbose) config process, chars in brackets are default values
	//config rows
	printf("Rows of cells?[%d]", ROW);
	flag = 1;
	while(flag){
		fgets(buf, sizeof(buf), stdin);
		if(buf[0] == '\n')//enter for default settings
			flag = 0;
		else{
			sscanf(buf, "%d", &tmp);
			if(tmp <= 0)
				printf("Illegal input!\nInput again:");
			else{
				ROW = tmp;//change setting
				flag = 0;
			}
		}
	}
	//config cols
	printf("Col of cells?[%d]", COL);
	flag = 1;
	while(flag){
		fgets(buf, sizeof(buf), stdin);
		if(buf[0] == '\n')//enter for default settings
			flag = 0;
		else{
			sscanf(buf, "%d", &tmp);
			if(tmp <= 0)
				printf("Illegal input!\nInput again:");
			else{
				COL = tmp;//change setting
				flag = 0;
			}
		}
	}
	ALL = COL * ROW;
	//ui
	printf("Character for living cells?(max %d)[%s]", MAXUILEN, ALIVE);
	flag = 1;
	while(flag){
		fgets(buf, sizeof(buf), stdin);
		if(buf[0] == '\n')//enter for default settings
			flag = 0;
		else{
			buf[strlen(buf) - 1] = '\0';
			strncpy(ALIVE, buf, MAXUILEN);
			flag = 0;
		}
	}
	printf("Character for died cells?(max %d)[%s]", MAXUILEN, DIE);
	flag = 1;
	while(flag){
		fgets(buf, sizeof(buf), stdin);
		if(buf[0] == '\n')//enter for default settings
			flag = 0;
		else{
			buf[strlen(buf) - 1] = '\0';
			strncpy(DIE, buf, MAXUILEN);
			flag = 0;
		}
	}
	//circle config
	printf("Enable circle or use border mode?(1 or 0)[%d]", CIRCLE);
	flag = 1;
	while(flag){
		fgets(buf, sizeof(buf), stdin);
		if(buf[0] == '\n')//enter for default settings
			flag = 0;
		else{
			flag = 0;
			sscanf(buf, "%d", &tmp);
			if(tmp == 0)
				CIRCLE = 0;
			else if(tmp == 1)
				CIRCLE = 1;
			else{
				flag = 1;
				printf("Illegal input!\nInput again:");
			}
		}
	}
	printf("config finished.\n");
}
int main(void)
{
	start();
	game();
	end();
	return 0;
}
