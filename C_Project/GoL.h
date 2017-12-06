/*
 * =====================================================================================
 *
 *       Filename:  GoL.h
 *
 *    Description:  Game of Life header file
 *
 *        Version:  1.0
 *        Created:  12/06/2017 05:23:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef GOL_H
#define GOL_H
//macre defines
#define BUFSIZE 10000
#define MAXUILEN 50

#define AUTHOR "guyimin"
#define INFO "PB17000002"
#define GITHUB "https://github.com/ustcpetergu"
#define PERCENT 50
//percentage of random cells
//macre defines end
//----config-------------------
extern int CELL_ALIVE_NUM[];//cell turn from die to alive
extern int CELL_KEEP_NUM[];//keep alive
//int CELL_DIE_NUM[] = {0, 1, 4, 5, 6, 7, 8, -1};
//not included in ALIVE and KEEP means turn to die
//you can change them for fun
//-1 means end

//cols and rols
//default 80 x 24 terminal, last line for status
extern int COL;
extern int ROW;
extern int ALL;//equals COL * ROW

//cell ui
//on windows
//char ALIVE[MAXUILEN] = "o";
//char DIE[MAXUILEN] = " ";
//on linux terminal
extern char ALIVE[MAXUILEN];//white block
extern char DIE[MAXUILEN];//black block

//is circle enabled? or border?
extern _Bool CIRCLE;
//----config end----------------

//main varaiables
typedef struct {
	_Bool alive;
	short neighbour;
}Cell;
extern Cell **map;//main cells
extern int alivenum;//number of living cells
extern double liverate;//percentage of living cells
//main varaiables end

//function list
void start();//initialization
void welcome();//show welcome msgs
void config();//config variables

void game();//main game loop
void randomize();//get a random living cells with PERCENT
void updatearound();//update living cell num around each cell
void updatecell();//update living status of each cell
void clearscreen();//clear the screen
void rewindcursor();//rewind cursor to home
void updatescreen();//rewind cursor, and print a new screen of cells

void end();//free and goodbye jobs
//function list end
#endif
