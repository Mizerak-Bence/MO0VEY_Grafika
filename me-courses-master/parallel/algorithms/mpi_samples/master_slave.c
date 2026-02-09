#include <mpi/mpi.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        printf("[%d] I am the master!\n", rank);
    }
    else {
        printf("[%d] I am just a slave.\n", rank);
    }
    MPI_Finalize();
    return 0;
}
