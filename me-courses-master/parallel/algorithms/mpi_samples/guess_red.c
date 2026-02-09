#include <mpi/mpi.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
    int rank;
    int n_tasks;
    float guess;
    float result;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0) {
        MPI_Comm_size(MPI_COMM_WORLD, &n_tasks);
        printf("[%04d] The number of tasks is %d.\n", rank, n_tasks);
        guess = 0.0;
    }
    else {
        guess = rank;
        printf("[%04d] I guess %f ...\n", rank, guess);
    }

    result = 0.0;
    printf("[%04d] Start reduction ...\n", rank);
    MPI_Reduce(&guess, &result, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        result /= (n_tasks - 1);
        printf("[%04d] The result is %f.\n", rank, result);
    }
    
    MPI_Finalize();
    return 0;
}
