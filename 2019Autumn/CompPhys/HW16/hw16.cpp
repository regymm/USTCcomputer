/**
 * File              : hw16.cpp
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

const int N = 500000;
const int Nskip = 100000;
const double sigmax = 1.;
const double sigmay = 1.;

// the Hamitonian of system
inline double H(double x, double y)
{
	return x*x / (2 * sigmax * sigmax) + y*y / (2 * sigmay * sigmay);
}


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
	// x and y is position of particle, H is the energy
	double x0;
	double y0;
	double H0;
	double xnew;
	double ynew;
	double Hnew;
	double delta = 0.1;
	double x2sum = 0;
	double y2sum = 0;
	double x2py2sum = 0;
	// initial position and energy
	x0 = 20;
	y0 = 20;
	H0 = H(x0, y0);
	int cnt = 0;
	for(int i = 0; i < N; i++) {
#ifndef NOVISUAL
		pt1.x = x0 * scale + offset;
		pt1.y = y0 * scale + offset;
#endif
		xnew = x0 + delta * (2 * randreal() - 1);
		ynew = y0 + delta * (2 * randreal() - 1);
		//cout << xnew << " " << ynew << endl;
		Hnew = H(xnew, ynew);
		double dH = Hnew - H0;
		// if energy becomes bigger, have some probability of refusing and keep old values
		if ((dH > 0) && randreal() > pow(M_E, -dH)) {
			// keep old values
		}
		// else accept new values
		else {
			// use new values
			x0 = xnew;
			y0 = ynew;
			H0 = Hnew;
		}
#ifndef NOVISUAL
		// draw a small line from old to new value, visualization.
		pt2.x = xnew * scale + offset;
		pt2.y = ynew * scale + offset;
		line(main_image, pt1, pt2, Scalar(255, 255, 255), 1, LINE_AA);
#endif
		// skip startup values
		if (i > Nskip) {
			x2sum += x0 * x0;
			y2sum += y0 * y0;
			x2py2sum += x0 * x0 + y0 * y0;
			cnt++;
		}
	}
	cout << cnt << endl;
	double x2avg = x2sum / (N - Nskip - 1);
	double y2avg = y2sum / (N - Nskip - 1);
	double x2py2avg = x2py2sum / (N - Nskip - 1);
	// here's the results
	cout << "x2avg: " << x2avg << endl;
	cout << "y2avg: " << y2avg << endl;
	cout << "x2py2avg: " << x2py2avg << endl;
#ifndef NOVISUAL
	// draw the central point 
	pt1.x = 0 + offset;
	pt1.y = 0 + offset;
	line(main_image, pt1, pt1, Scalar(0, 255, 0), 10, LINE_AA);
	imshow(main_name, main_image);
	waitKey();
#endif
	return 0;
}
