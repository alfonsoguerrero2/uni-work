/* Sending data in a ring 
* K Djemame
* September 2024
*/

#include <stdio.h>
#include "mpi.h"

int main( argc, argv )
int argc;
char **argv;
{
    int rank, value, size;
    MPI_Status status;

    MPI_Init( &argc, &argv );

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

   char         processorname[100];
   int          namelen;
   MPI_Get_processor_name( processorname, &namelen );
	
    if (rank == 0) {
        //try printing the size and rank//
        printf("%d", rank);
	    printf("Input a value : ");
        fflush(stdout);
        scanf( "%d", &value );
	    MPI_Send( &value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD );
	}
    
	else {
	    MPI_Recv( &value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, 
		      &status );
            value++;
	    if (rank < size - 1)
            {
		    MPI_Send( &value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD );
            }
        else {
            // If it's the last process, send the value back to process 0
            MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
	}
	printf( "Process %d on %s got %d\n", rank, processorname, value );
    fflush(stdout);
    MPI_Finalize( );
    return 0;
}

