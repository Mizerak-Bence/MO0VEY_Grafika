#include <mpi/mpi.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
    int rank;
    int message;
    int destination;
    int tag;
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        printf("[%04d] I am the sender!\n", rank);
        message = 42;
        destination = 1;
        tag = 1;
        printf("[%04d] Start sending ...\n", rank);
        MPI_Send(&message, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
        printf("[%04d] Message has sent!\n", rank);
    }
    else {
        printf("[%04d] I am the receiver!\n", rank);
        printf("[%04d] Wait for a message ...\n", rank);
        MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("[%04d] The received message is %d.\n", rank, message);
        printf("[%04d] The sender's rank is %d.\n", rank, status.MPI_SOURCE);
    }
    MPI_Finalize();
    return 0;
}
