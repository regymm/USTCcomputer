#include <iostream>
//#include "Matrix.h"
using namespace std;

#define THREAD_NUM 8

typedef struct{
	int n;
	double* elem;
}SMat;
void Create(SMat* mat, int n)
{
	mat->n = n;
	mat->elem = (double*)malloc(sizeof(double) * n * n);
}
void Destroy(SMat* mat)
{
	free(mat->elem);
}
void Zero(SMat* mat)
{
	int i;
	for(i = 0; i < mat->n * mat->n; i++)
		mat->elem[i] = 0;
}
void Print(SMat* mat)
{
	int i, j;
	for(i = 0; i < mat->n; i++) {
		for(j = 0; j < mat->n; j++)
			cout << mat->elem[i * mat->n + j] << " ";
		cout << endl;
	}
}
void randmat(SMat* mat, double mini, double maxi)
{
	for(int i = 0; i < mat->n * mat->n; i++) {
		mat->elem[i] = (maxi - mini) * (double) rand() / (RAND_MAX) + mini;
	}
}
double naive_ijk(SMat* a, SMat* b, SMat* c)
{
	clock_t start;
	clock_t end;
	start = clock();
	int i, j, k;
	double sum;
	int n = a->n;
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			sum = 0.0;
			for(k = 0; k < n; k++) {
				sum += a->elem[i * n + k] * b->elem[k * n + j];
			}
			c->elem[i * n + j] += sum;
		}
	}
	end = clock();
	return (end - start) / (double)CLOCKS_PER_SEC * 1000;
}
double naive_jik(SMat* a, SMat* b, SMat* c)
{
	clock_t start;
	clock_t end;
	start = clock();
	int i, j, k;
	double sum;
	int n = a->n;
	for(j = 0; j < n; j++) {
		for(i = 0; i < n; i++) {
			sum = 0.0;
			for(k = 0; k < n; k++) {
				sum += a->elem[i * n + k] * b->elem[k * n + j];
			}
			c->elem[i * n + j] += sum;
		}
	}
	end = clock();
	return (end - start) / (double)CLOCKS_PER_SEC * 1000;
}
double naive_jki(SMat* a, SMat* b, SMat* c)
{
	clock_t start;
	clock_t end;
	start = clock();
	int i, j, k;
	double r;
	int n = a->n;
	for(j = 0; j < n; j++)
		for(k = 0; k < n; k++) {
			r = b->elem[k * n + j];
			for(i = 0; i < n; i++)
				c->elem[i * n + j] += a->elem[i * n + k] * r;
		}
	end = clock();
	return (end - start) / (double)CLOCKS_PER_SEC * 1000;
}
double naive_kij(SMat* a, SMat* b, SMat* c)
{
	clock_t start;
	clock_t end;
	start = clock();
	int i, j, k;
	double r;
	int n = a->n;
	for(k = 0; k < n; k++)
		for(i = 0; i < n; i++) {
			r = a->elem[i * n + k];
			for(j = 0; j < n; j++)
				c->elem[i * n + j] += r * b->elem[k * n + j];
		}
	end = clock();
	return (end - start) / (double)CLOCKS_PER_SEC * 1000;
}
double naive_kji(SMat* a, SMat* b, SMat* c)
{
	clock_t start;
	clock_t end;
	start = clock();
	int i, j, k;
	double r;
	int n = a->n;
	for(k = 0; k < n; k++)
		for(j = 0; j < n; j++) {
			r = b->elem[k * n + j];
			for(i = 0; i < n; i++)
				c->elem[i * n + j] += r * a->elem[i * n + k];
		}
	end = clock();
	return (end - start) / (double)CLOCKS_PER_SEC * 1000;
}
double naive_ikj(SMat* a, SMat* b, SMat* c)
{
	clock_t start;
	clock_t end;
	start = clock();
	int i, j, k;
	double r;
	int n = a->n;
	for(i = 0; i < n; i++)
		for(k = 0; k < n; k++) {
			r = a->elem[i * n + k];
			for(j = 0; j < n; j++)
				c->elem[i * n + j] += r * b->elem[k * n + j];
		}
	end = clock();
	return (end - start) / (double)CLOCKS_PER_SEC * 1000;
}

double bijk(SMat* a, SMat* b, SMat* c, int bsize)
{
	clock_t start;
	clock_t end;
	double sum;
	int n = a->n;
	start = clock();
	int i, j, k, jj, kk;
	for (jj=0; jj<n; jj+=bsize) {
	  //for (i=0; i<n; i++)
	    //for (j=jj; j < min(jj+bsize,n); j++)
	      //c->elem[i * n + j] = 0.0;
	  for (kk=0; kk<n; kk+=bsize) { 
	    for (i=0; i<n; i++) {
	      for (j=jj; j < jj+bsize; j++) { 
		sum = 0.0;
		for (k=kk; k < kk+bsize; k++) {
		  sum += a->elem[i * n + k] * b->elem[k * n + j];
		}
		c->elem[i * n + j] += sum;
	      }
	    }
	  }
	}

	end = clock();
	return (end - start) / (double)CLOCKS_PER_SEC * 1000;
}
//double bikj(SMat* a, SMat* b, SMat* c, int bsize)
//{
	//clock_t start;
	//clock_t end;
	//double r;
	//int n = a->n;
	//start = clock();
	//for(int ii = 0; ii < n; ii += bsize) {
		//for(int kk = 0; kk < n; kk += bsize) {
			//for(int k = kk; k < min(kk + bsize, n); k++) {
				//r = a->elem[i * n + k];
				//for(int j = jj; j < min(jj + bsize, n); j++)
					//c->elem[ii * n + j] += r * b->elem[k * n + j];

			//}
		//}
	//}

	//for(int i = 0; i < n; i++)
		//for(int k = 0; k < n; k++) {
			//r = a->elem[i * n + k];
			//for(int j = 0; j < n; j++)
				//c->elem[i * n + j] += r * b->elem[k * n + j];
		//}
	//end = clock();
	//return (end - start) / (double)CLOCKS_PER_SEC * 1000;
//}

void naiveP(SMat* a, SMat* b, SMat* c)
{

}


int main(int argc, char** argv)
{
	srand(unsigned(time(0)));
	SMat A, B, C;
	int N = 1000;
	Create(&A, N);
	Create(&B, N);
	Create(&C, N);
	randmat(&A, 0, 1);
	randmat(&B, 0, 1);
	naive_ijk(&A, &B, &C);
	//Print(&C);
	Zero(&C);
	//Print(&A);
	//Print(&B);
	double times = 0, time;
	for(int i = 0; i < 5; i++) {
		Zero(&C);
		time = bijk(&A, &B, &C, 25);
		times += time;
		cout << "Time: " << time << endl;
	}
	cout << "Avg. Time: " << times / 5.0 << endl;
	//Print(&C);
	Destroy(&A);
	Destroy(&B);
	Destroy(&C);
	return 0;
}
