/* mpi Bradcast 
* K Djemame
* September 2024
*/

#include <stdio.h>
#include "mpi.h"

int main( argc, argv )
int argc;
char **argv;
{
    int rank, size, temp, local_result, total_sum;
    MPI_Init( &argc, &argv );

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    do {
	if (rank == 0)
	{ 
            printf("Input a number: ");
            fflush(stdout);
	    scanf( "%d", &temp );
        }
	MPI_Bcast( &temp, 1, MPI_INT, 0, MPI_COMM_WORLD );
	if (temp >= 0) {
            // Each process calculates the result as temp * rank
            local_result = temp * rank;

            // Use MPI_Reduce to sum up the results from all processes at rank 0
            MPI_Reduce(&local_result, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

            // Process 0 prints the overall sum
            if (rank == 0) {
                printf("Total sum of temp * rank across all processes: %d\n", total_sum);
                temp = -1; 
            }
        }



	    printf( "Process %d got %d\n", rank, temp );
    } while (temp >= 0);

    MPI_Finalize( );
    return 0;
}

