/**r2avg
 * File              : hw11.c
 * License           : GPL-3.0-or-later
 * Author            : Yimin Gu <github.com/ustcpetergu>
 * Date              : 2019.10.27
 * Last Modified Date: 2019.10.29
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// the dimensions of SAW
#define DIM 2
// N the max size of SAW
#define NMAX 3000

// M the total tries
int M = 5000;

typedef struct _corr {
	int x[DIM];
} Corr;

// N the step, w the weight, history the history
typedef struct _path {
	int N;
	double w[NMAX + 10];
	Corr history[NMAX + 10];
} Path;

// the classical trick
int d[][2] = {{ 0,-1}, { 0, 1}, { 1, 0}, {-1, 0}}; 
// use this to recored history, trade memory for time
int playground[NMAX * 2 + 10][NMAX * 2 + 10];
// r2avg to record the final results
double r2avg[NMAX] = {0};
// wsumarr to record \sigma_i{w_i(N)} for each N
double wsumarr[NMAX] = {0};


// playground: the graph handling
void setplayground(Corr c)
{
	playground[c.x[0] + NMAX][c.x[1] + NMAX] = 1;
}

int  getplayground(Corr c)
{
	return playground[c.x[0] + NMAX][c.x[1] + NMAX];
}

int getavail(Corr c, int dir)
{
	return !playground[c.x[0] + NMAX + d[dir][0]][c.x[1] + NMAX + d[dir][1]];
}

// saw: do a N step SAW try, return 0/1 for fail/success
// whole path will be recored in p
int saw(int N, Path* p)
{
	memset(playground, 0, (NMAX * 2 + 10) * (NMAX * 2 + 10) * sizeof(int));
	Corr corr;
	corr.x[1] = corr.x[0] = 0;
	/*p->history[0] = corr;*/
	setplayground(corr);
	int i, j, k;
	double w;
	w = 1;
	p->N = N;
	for(i = 0; i < N; i++) {
		k = 0;
		int availchoice[4];
		int availnum = 0;
		for(j = 0; j < 4; j++) {
			if(getavail(corr, j)) {
				availnum++;
				availchoice[k++] = j;
			}
		}
		if (availnum == 0) {
			/*p->w[i] = 0;*/
			return 0;
		}
		int choice = availchoice[rand() % availnum];
		corr.x[0] += d[choice][0];
		corr.x[1] += d[choice][1];
		/*printf("%d %d\n", d[choice][0], d[choice][1]);*/
		setplayground(corr);
		p->history[i] = corr;
		w *= (double)availnum / 3.;
		p->w[i] = w;
	}
	return 1;
}

void saw_till_success(int N, Path* p)
{
	/*int i = 0;*/
	while(!saw(N, p)) {
		/*i++;*/
		/*fprintf(stderr, "WARNING: SAW failed: %d\n", i);*/
	}
	/*printf("INFO: SAW success\n");*/
}

int main(int argc, char* argv[])
{
	srand((unsigned)time(0));
	int i, j, k;
	int N = 50;
	Path p;
	if (argc == 2 && strcmp(argv[1], "map") == 0) {
		saw_till_success(N, &p);
		// the (0, 0) is not recored in array, print manually
		printf("0 ");
		for(i = 0; i < N; i++) {
			printf("%d ", p.history[i].x[0]);
		}
		printf("\n");
		printf("0 ");
		for(i = 0; i < N; i++) {
			printf("%d ", p.history[i].x[1]);
		}
		printf("\n");
		return 0;
	}
	// repeat computation, use p as Path variable, discard p after done a loop
	for(i = 0; i < M; i++) {
		// a user friendly dynamic progress display
		if ((i % 100) == 0) {
			fprintf(stderr, "\r(%d/%d) ...", i, M - 1);
		}
		saw_till_success(N, &p);
		for(j = 0; j < N; j++) {
			r2avg[j] += p.w[j] * (p.history[j].x[0]*p.history[j].x[0] + p.history[j].x[1]*p.history[j].x[1]);
			/*printf("->%lf\n", p.w[j]);*/
			wsumarr[j] += p.w[j];
		}
		/*printf("%d %d\n", p.history[N - 1].x[0], p.history[N - 1].x[1]);*/
	}
	for(i = 0; i < N; i++) {
		/*printf("%lf %lf \n", r2avg[i], wsumarr[i]);*/
		r2avg[i] /= wsumarr[i];
	}
	/*printf("\n");*/
	for(i = 0; i < N; i++) {
		printf("%lf ", r2avg[i]);
	}
	printf("\n");
	return 0;
}
