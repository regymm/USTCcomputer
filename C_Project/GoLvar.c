/*
 * =====================================================================================
 *
 *       Filename:  GoLvar.c
 *
 *    Description:  Game of Life global variables
 *
 *        Version:  1.0
 *        Created:  12/06/2017 05:42:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include "GoL.h"

int CELL_ALIVE_NUM[] = {3, -1};
int CELL_KEEP_NUM[] = {2, 3, -1};

int COL = 40;
int ROW = 23;
int ALL;

char ALIVE[MAXUILEN] = "\033[47m  \033[0m";
char DIE[MAXUILEN] = "\033[40m  \033[0m";

_Bool CIRCLE = 0;

Cell **map;
int alivenum = 0;
double liverate = 0.0;
