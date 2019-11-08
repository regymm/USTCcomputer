/**
 * File              : hw13.cpp
 * License           : GPL-3.0-or-later
 * Author            : Yimin Gu <github.com/ustcpetergu>
 * Date              : 2019.11.05
 * Last Modified Date: 2019.11.05
 */
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#ifndef NOVISUAL
//#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#endif

using namespace std;
#ifndef NOVISUAL
using namespace cv;
#endif

//macros for random mode, just ignore this. 
#define SQR 1001
#define CIR 1002
// playground: arena of simulation, store all occupied location
const int MaxSize = 500;
short int playground[MaxSize * 2 + 1][MaxSize * 2 + 1] = {0};
// the classical trick
int d[][2] = {{ 0,-1}, { 0, 1}, { 1, 0}, {-1, 0}}; 


inline void setplayground(int x, int y)
{
	playground[MaxSize + x][MaxSize + y] = 1;
}

inline int getplayground(int x, int y)
{
	return playground[MaxSize + x][MaxSize + y];
}

// judge whether the particle walks into illegal area(out of boundary)
inline int legal(int mode, int x, int y)
{
	return (mode == SQR && -MaxSize <= x && x <= MaxSize && -MaxSize <= y && y <= MaxSize) || \
		(mode == CIR && x*x + y*y <= MaxSize * MaxSize);
}

void printplayground()
{
	int i, j;
	for(i = 0; i <= MaxSize * 2; i++) {
		for(j = 0; j <= MaxSize * 2; j++)
			printf("%c ", playground[i][j] ? '*' : '.');
		printf("\n");
	}
}

void initialize()
{
	srand((unsigned)time(0));
	// set the core seed(a 2n*2n block of 1s) of the DLA
	int i, j;
	int n = 4;
	// set up the initial seeds: a small square
	// single core or multiple cores
	for(i = -n; i < n; i++)
		for(j = -n; j < n; j++)
			setplayground(i, j);
	//for(i = -n; i < n; i++)
		//for(j = -n; j < n; j++)
			//setplayground(i + 15, j + 15);
	//for(i = -n; i < n; i++)
		//for(j = -n; j < n; j++)
			//setplayground(i - 15, j - 15);
	//for(i = -n; i < n; i++)
		//for(j = -n; j < n; j++)
			//setplayground(i + 15, j - 15);
	//for(i = -n; i < n; i++)
		//for(j = -n; j < n; j++)
			//setplayground(i - 15, j + 15);
	// have a try of boundary condition as a line
	//for(i = -MaxSize; i < MaxSize; i++)
		//setplayground(i, 0);
	// have a try of semicircle boundary
	//for(i = 0; i < 1000; i++)
		//setplayground(MaxSize / 2. * sin(i / 1000. * M_PI), MaxSize / 2. * cos(i / 1000. * M_PI));
}

// get a random start location
inline void random_start_location(int mode, int& startx, int& starty)
{
	if(mode == SQR) {
		// the square boudary, random side and random location on side
		int range = MaxSize;
		switch (rand() % 4) {
			case 0:
				startx = -range;
				starty = rand() % (range * 2) - range;
				break;
			case 1:
				startx = +range;
				starty = rand() % (range * 2) - range;
				break;
			case 2:
				starty = -range;
				startx = rand() % (range * 2) - range;
				break;
			case 3:
				starty = +range;
				startx = rand() % (range * 2) - range;
				break;
			default:
				exit(-1);
		}
	}
	if(mode == CIR) {
		// circular boundary, fix $r$, random $\theta$
		double theta = rand() / (double) RAND_MAX * 2 * M_PI;
		startx = MaxSize * cos(theta);
		starty = MaxSize * sin(theta);
	}
}

typedef struct _corr {
	int x;
	int y;
}Corr;

// Do a random walk from a random start position till 
// particle get attached to main structure. 
// This is the main process
Corr do_random_walk()
{
	int startx;
	int starty;
	int dx;
	int dy;
	int i;
	int choice;
	int mode = CIR;
	random_start_location(mode, startx, starty);
	// do walk till meet main structure
	while(1) {
		choice = rand() % 4;
		startx += d[choice][0];
		starty += d[choice][1];
		// walked out of arena, backtrack. 
		if(!legal(mode, startx, starty)) {
			startx -= d[choice][0];
			starty -= d[choice][1];
			continue;
		}
		// bumped into main structure, accept: 
		// set the location before bumping as occupied(main structure grows a new particle)
		// and finish walking.
		if(getplayground(startx, starty)) {
			setplayground(startx - d[choice][0], starty - d[choice][1]);
			return {startx - d[choice][0], starty - d[choice][1]};
		}
		// if this step is walked successfully, just go on and do nothing
	}

}

// DLA simulation

int main(int argc, char* argv[])
{
	int Nstep = 50000;
	int i, j;
	double N;
	double Rg2;
	double r2sum = 0;

#ifndef NOVISUAL
	// Visualize. Using OpenCV.
	int scale = 1;
	int delay = 5;
	int height = (MaxSize * 2 + 1) * scale;
	int width = (MaxSize * 2 + 1) * scale;
	const int Delay = 5;
	char main_name[] = "Drawing: DLA result";
	Mat main_image = Mat::zeros(height, width, CV_8UC3);
	Point p;
	imshow(main_name, main_image);
#endif

	//sscanf(argv[1], "%d", &Nstep);
	
	initialize();
	for(i = 0; i < Nstep; i++) {
		// user-friendly progress bar
		fprintf(stderr, "\r(%d/%d) done...", i, Nstep);
		Corr pp = do_random_walk();
#ifndef NOVISUAL
		// real time graphics
		p.x = (pp.x + MaxSize) * scale;
		p.y = (pp.y + MaxSize) * scale;
		circle(main_image, p, 1, Scalar(255, 255, 255 * (1 - i / ((double) Nstep))), scale);
		if(!(i % 10)) { 
			imshow(main_name, main_image);
			waitKey(delay);
		}
#endif
		// calculate N-Rg
		// N: area
		N = i + 1;
		printf("%lf ", N);
		// Rg^2=simga(r_i^2)/N, reuse old value to avoid re-calculation
		r2sum += pp.x * pp.x + pp.y * pp.y;
		Rg2 = r2sum / N;
		printf("%lf\n", Rg2);
	}
#ifndef NOVISUAL
	//printplayground();
	
	//for(i = 0; i < MaxSize * 2 + 1; i++)
		//for(j = 0; j < MaxSize * 2 + 1; j++)
			//if (playground[i][j]) {
				//p.x = i * scale;
				//p.y = j * scale;
				//circle(main_image, p, 1, Scalar(255, 255, 255), scale);
			//}
	// draw the source circle if boundary condition is circular, to make graph better
	//p.x = p.y = MaxSize * scale;
	//circle(main_image, p, MaxSize * scale, Scalar(255, 255, 255), scale);
	imshow(main_name, main_image);
	waitKey();
#endif
	return 0;
}
