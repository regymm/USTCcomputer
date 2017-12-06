/*
 * =====================================================================================
 *
 *       Filename:  GoLui.c
 *
 *    Description:  Game of Life ui
 *
 *        Version:  1.0
 *        Created:  12/06/2017 05:23:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "GoL.h"
void clearscreen()
{
	printf("\033[2J");
}
void rewindcursor()
{
	printf("\033[H");
}
void updatescreen()
{
	rewindcursor();
	int i, j;
	for(i = 0; i < COL; i++){
		for(j = 0; j < ROW; j++){
			if(map[i][j].alive == 1)
				printf("%s", ALIVE);
			else printf("%s", DIE);
		}
		printf("\n");
	}

}
void welcome(){
	printf("-----------------------------\n");
	printf("C Programming Project -- Game of Life\n");
	printf("https://en.wikipedia.org/wiki/Conway%%27s_Game_of_Life\n");
	printf("Run in linux to get best performance\n");
	printf("\t2017, writen by %s (%s)\n", AUTHOR, INFO);
	printf("\tCode also available on %s\n", GITHUB);
	printf("\n");
	printf("In game: press ENTER to next move, a to auto move, q ro quit\n");
	printf("-----------------------------\n\n");
}
