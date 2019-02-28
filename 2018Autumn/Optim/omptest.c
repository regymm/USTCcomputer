#include <stdio.h>
#include "omp.h"

#define N 100
int main()
{
#pragma omp parallel num_threads(5)
	{
		printf("Hello openmp!\n");
	}
#pragma omp parallel for
	for(int i = 0; i < N; i++)
		printf("%d ", i);
	return 0;
}
