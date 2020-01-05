#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "mpi.h"

#define N 10

int main(int argc, char* argv[])
{
	int rank, size, len;
	char version[MPI_MAX_LIBRARY_VERSION_STRING];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Get_library_version(version, &len);

	// father process
	if (rank == 0) {
		float resultmat[N][N];
		int i, j, k;
		printf("Father start...\n");
		int childid;
		for (i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				float max = -9e9; 
				float buf;
				MPI_Status status;
				for (k = 1; k < size; k++) {
					/*printf("Father>Prepare to receive signal\n");*/
					MPI_Recv(&buf, 1, MPI_FLOAT, k, i * N + j, MPI_COMM_WORLD, &status);
					/*printf("Father>Signal received.\n");*/
					max = buf > max ? buf : max;
				}
				resultmat[i][j] = max; 
			}
		}
		printf("Maximum: \n");
		for (i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				printf("%f ", resultmat[i][j]);
			}
			printf("\n");
		}
		printf("Father end. \n");
		/*for (childid = 0; childid < size; childid++) {*/
			/*MPI_Send(buf, count, datatype, dest, tag, MPI_COMM_WORLD);*/
		/*}*/
	}
	// children processes
	else {
		srand((unsigned)time(0) * rank);
		float randmat[N][N];
		int i, j;
		char filename[100];
		sprintf(filename, "data_%d.txt", rank);
		FILE* fout = fopen(filename, "w");
		fprintf(fout, "Child %d\n", rank);
		for (i = 0; i < N; i++) {
			/*printf("%d>", rank);*/
			for(j = 0; j < N; j++) {
				randmat[i][j] = rand() / (double) RAND_MAX;
				fprintf(fout, "%f ", randmat[i][j]);
			}
			fprintf(fout, "\n");
		}
		fclose(fout);
		for (i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				// send the (i,j) element to father
				/*MPI_Send(&randmat[i][j], 1, MPI_FLOAT, 0, i * N + j, MPI_COMM_WORLD);*/
				MPI_Send(&randmat[i][j], 1, MPI_FLOAT, 0, i * N + j, MPI_COMM_WORLD);
				/*printf("%d>Sent signal %d\n", rank, i * N + j);*/
			}
		}

	}
	MPI_Finalize();
	return 0;
}
