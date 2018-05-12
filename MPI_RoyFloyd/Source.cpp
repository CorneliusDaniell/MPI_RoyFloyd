#include "mpi.h" 
#include <stdio.h> 
#include <stdlib.h> 
#define  MASTER 0
#define N 4


int main(int argc, char *argv[]) {

	int procsSize, idProc, i=0, j=0, k=0;
	int m[N][N] = { { 0, 5, 3, 10 },
	{ 5, 0, 3, 4 },
	{ 3, 3, 0, 1 },
	{ 10, 4, 1, 0 } };
	int s[N][N];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &procsSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &idProc);
	MPI_Status status;

	if (idProc == MASTER)
	{
		for (i = 1; i < procsSize; i++)
		{
			for (j = 1; j < N; j++)
			{
				MPI_Send(&m[i][j], 1, MPI_INT, i, i, MPI_COMM_WORLD);
			}
		}
	}
	else
	{
		MPI_Recv(&s, N, MPI_INT, i, i, MPI_COMM_WORLD, &status);
		for (int k = 0; k < N; k++)
		{
			i = idProc;
			for (int j = 0; j < N; j++)
			if (s[i][j] > s[i][k] + s[k][j])
			{
				s[i][j] = s[i][k] + s[k][j];
			}

			MPI_Alltoall(&s, N, MPI_INT, &m, N, MPI_INT, MPI_COMM_WORLD);
		}

	}
	MPI_Finalize();
}




