/**
 * File              : hw17.cpp
 * License           : GPL-3.0-or-later
 * Author            : Yimin Gu <github.com/ustcpetergu>
 * Date              : 2019.12.10
 * Last Modified Date: 2019.12.10
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

// iteration times
const int N = 100000;
// particle numbers
const int P = 10000;
// record the velocity of particles
double velocity[P] = {0};
double v0 = 2.;
// demon energy
double demonE = 0.;
// total energy
double allE = 0.;
// temperature
double T;
// Boltzmann constant is set to 1 implicitely


// random real number in [0, 1]
inline double randreal()
{
	return (double) rand() / (RAND_MAX);
}

void initialize()
{
	srand((unsigned)time(0));
}


int main(int argc, char* argv[])
{
#ifndef NOVISUAL
	// Visualize. Using OpenCV.
	int scale = 20;
	int delay = 5;
	int width = 1000;
	int offset = width / 2;
	const int Delay = 5;
	char main_name[] = "Drawing: Metropolis MC result";
	Mat main_image = Mat::zeros(width, width, CV_8UC3);
	imshow(main_name, main_image);
	Point pt1;
	Point pt2;
#endif
	initialize();
	// initialize velocities, start at uniform distribution
	for (int i = 0; i < P; i++) {
		velocity[i] = v0 * (2 * randreal() - 1);
	}
	// calculate initial total energy
	for (int i = 0; i < P; i++) {
		allE += 0.5 * velocity[i] * velocity[i];
	}
	double vold;
	double vnew;
	double dE;
	double deltav = 0.5;
	// calculate the acception rate
	int acc = 0;
	for(int i = 0; i < N; i++) {
		// randomly pick a particle
		int id = rand() % P;
		vold = velocity[id];
		// try a move: new velocity
		vnew = vold + (2 * randreal() - 1) * deltav;
		dE = 0.5 * (vnew * vnew - vold * vold);
		if ( dE <= 0 || demonE >= dE) {
			// accept movement
			velocity[id] = vnew;
			demonE -= dE;
			allE += dE;
			acc++;
			T = 2 * allE / P;
			cout << "" << T << "\t" << allE << "\t" << demonE << endl;
		}
		// else reject movement
	}
	// simulation end, calculate results
	// print the final velocities for histogram
	for(int i = 0; i < P; i++) {
		cout << velocity[i] << endl;
	}
	double vavg = 0;
	for(int i = 0; i < P; i++) {
		vavg += velocity[i];
	}
	vavg = vavg / P;
	double vvar = 0;
	for(int i = 0; i < P; i++) {
		vvar += (velocity[i] - vavg) * (velocity[i] - vavg);
	}
	vvar /= P;
	cerr << "Average velocity: " << vavg << endl;
	cerr << "velocity variances: " << vvar << endl;
	cerr << "Acception rate: " << (double) acc / N << endl;
	//cout << cnt << endl;
	//double x2avg = x2sum / (N - Nskip - 1);
	//double y2avg = y2sum / (N - Nskip - 1);
	//double x2py2avg = x2py2sum / (N - Nskip - 1);
	//cout << "x2avg: " << x2avg << endl;
	//cout << "y2avg: " << y2avg << endl;
	//cout << "x2py2avg: " << x2py2avg << endl;
#ifndef NOVISUAL
	imshow(main_name, main_image);
	waitKey();
#endif
	return 0;
}
