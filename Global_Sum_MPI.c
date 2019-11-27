#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/**
 * Global Sum MPI
 *
 * This program has each process create a random
 * number from (0-99) and adds the numbers.
 *
 * @Author: Clayton Chase Glenn
 */

int Global_sum(int my_int, int my_rank, int comm_sz, MPI_Comm comm){  
  if(my_rank != 0){   
    if(!MPI_Send(&my_int, 1, MPI_INT, 0, 0, comm)){      
      return -1;   
    } 
  } else {   
    int total = my_int;   
    for(int q = 1; q < comm_sz; q++){     
      if(!MPI_Revc(my_int, 1, MPI_INT, q, 0, comm, MPI_STATUS_IGNORE)){       
        return -1;    
      }     
      total = total + my_int; 
    } 
    return total;
  }


int main(int argc, char* argv[]) {
   int p, my_rank;
   MPI_Comm comm;
   int sum;
   MPI_Init(&argc, &argv);
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(comm, &p);
   MPI_Comm_rank(comm, &my_rank);
   srandom(my_rank+1);
   int my_number = random() % 100;
   printf("Proc %d > my_number = %d\n", my_rank, my_number);
   sum = Global_sum(my_number, my_rank, p, comm);
   if (my_rank == 0) printf("Proc %d > global sum = %d\n", my_rank, sum);
   MPI_Finalize();
   return 0;
}  /* main */
