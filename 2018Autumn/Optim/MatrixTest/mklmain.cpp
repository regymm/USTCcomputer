#include <iostream>
#include "Matrix.h"
#include <ctime>
#include <cstdio>
using namespace std;

void randmat(matrix& mat, double mini, double maxi)
{
	for(int i = 0; i < mat.Col * mat.Row; i++) {
		mat.Elem[i] = (maxi - mini) * (double) rand() / (RAND_MAX) + mini;
	}
}

double mul_test(matrix& mat1, matrix& mat2, matrix& mat3)
{
	clock_t start;
	clock_t end;
	start = clock();
	mat3 = mat1 * mat2;
	end = clock();
	return (end - start) / (double)CLOCKS_PER_SEC * 1000;
}


int main()
{
	srand(unsigned(time(0)));
	int m = 10, n = 2;
	matrix A = matrix(n, n, 0.0);
	matrix B = matrix(n, n, 1.0);
	matrix C;
	randmat(A, 0, 1);
	randmat(B, 0, 1);
	double times = 0, time;
	for(int i = 0; i < 10; i++) {
		time = mul_test(A, B, C);
		times += time;
		cout << "Time: " << time << endl;
	}
	cout << "Avg. Time: " << times / 10.0 << endl;
	C.show();
	
	A.show();
	B.show();
	return 0;
}


