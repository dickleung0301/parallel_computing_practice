#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[]){
	int task_rank; // declare the variables used in mpi
	int num_process;
	MPI_Init(&argc, &argv); // start the mpi session
	MPI_Comm_size(MPI_COMM_WORLD, &num_process); // to get the no. of process via pass by reference
	MPI_Comm_rank(MPI_COMM_WORLD, &task_rank); // to get the task no. at each process
	std::cout << "Task " << task_rank << " from " << num_process << " Tasks." << std::endl;
	MPI_Finalize();
}
