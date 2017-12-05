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

//macre defines
#define BUFSIZE 10000
#define MAXUILEN 50

#define AUTHOR "guyimin"
#define INFO "PB17000002"
#define GITHUB "https://github.com/ustcpetergu"
//----config--------

//main data
int CELL_ALIVE_NUM[] = {3, -1};//cell turn from die to alive
int CELL_KEEP_NUM[] = {2, 3, -1};//keep alive
int CELL_DIE_NUM[] = {0, 1, 4, 5, 6, 7, 8, -1};//turn to die
//you can change them for fun
//-1 means end

//cols and rols
//default 80 x 24 terminal, last line for status
int COL = 80;
int ROW = 23;

//cell ui
//char ALIVE[MAXUILEN] = "o";
//char DIE[MAXUILEN] = " ";
char ALIVE[MAXUILEN] = "\033[47m  \033[0m";
char DIE[MAXUILEN] = "\033[40m  \033[0m";

//is circle enabled?
_Bool CIRCLE = 0;

//----config end----

//function list
void start();
void welcome();
void config();

void game();

void end();
//function list end
//main varaiables
typedef struct {
	_Bool alive;
	short neighbour;
}Cell;
Cell **map;//main cells
int cellnum;//number of cells
int alivenum = 0;//number of living cells
double liverate = 0.0;//percentage of living cells
//main varaiables end
void game()
{
}
void end()
{
}
int main(void)
{
	start();
	game();
	end();
	return 0;
}

void start()
{
	welcome();
	config();
}
void welcome(){
	printf("-----------------------------\n");
	printf("C Programming Project\n");
	printf("2017, writen by %s (%s)\n", AUTHOR, INFO);
	printf("Code also available on %s\n", GITHUB);
	printf("Game of Life\n");
	printf("https://en.wikipedia.org/wiki/Conway%%27s_Game_of_Life\n");
	printf("-----------------------------\n\n");
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
