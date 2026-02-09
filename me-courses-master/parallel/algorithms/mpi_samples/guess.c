#include <mpi/mpi.h>

#include <stdio.h>

void send_guess(int rank)
{
    float guess;
    int destination;
    int tag;

    guess = rank;
    destination = 0;
    tag = 1;
    printf("[%04d] Send %f to 0 ...\n", rank, guess);
    MPI_Send(&guess, 1, MPI_FLOAT, destination, tag, MPI_COMM_WORLD);
    printf("[%04d] Message has sent!\n", rank);
}

void collect_guesses(int rank)
{
    int n_tasks;
    int n_received_guesses;
    float guess;
    MPI_Status status;
    float sum;
    
    MPI_Comm_size(MPI_COMM_WORLD, &n_tasks);
    n_received_guesses = 0;
    
    printf("[%04d] I wait %d guesses.\n", rank, n_tasks - 1);
    sum = 0.0;
    while (n_received_guesses < n_tasks - 1) {
        MPI_Recv(&guess, 1, MPI_FLOAT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("[%04d] I received %f from %d.\n", rank, guess, status.MPI_SOURCE);
        sum += guess;
        ++n_received_guesses;
    }
    printf("[%04d] All guesses has received!\n", rank);
    printf("[%04d] The result is %f.\n", rank, sum / n_received_guesses);
}

int main(int argc, char* argv[])
{
    int rank;
    float guess;
    int destination;
    int tag;
    MPI_Status status;
    
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
