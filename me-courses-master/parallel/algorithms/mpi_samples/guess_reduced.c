#include <mpi/mpi.h>

#include <stdio.h>

void send_guess(int rank)
{
    float guess;
    float result;

    guess = rank;
    result = 0.0;
    printf("[%04d] I guess %f ...\n", rank, guess);
    MPI_Reduce(&guess, &result, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    printf("[%04d] I will return.\n", rank);
}

void collect_guesses(int rank)
{
    int n_tasks;
    float guess;
    float result;
    
    MPI_Comm_size(MPI_COMM_WORLD, &n_tasks);
    printf("[%04d] The number of tasks is %d.\n", rank, n_tasks);
    printf("[%04d] Start reduction ...\n", rank);
    guess = 0.0;
    result = 0.0;
    MPI_Reduce(&guess, &result, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    result /= (n_tasks - 1);
    printf("[%04d] The result is %f.\n", rank, result);
}

int main(int argc, char* argv[])
{
    int rank;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank > 0) {
        send_guess(rank);
    }
    else {
        collect_guesses(rank);
    }
    MPI_Finalize();
    return 0;
}
