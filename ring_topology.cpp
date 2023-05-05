#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[]){

	int task_rank;
	int num_process;
	int previous_task;
	// MPI_Status status; // a struct to represent the status of received messgae
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &task_rank); // to get the task rank
	MPI_Comm_size(MPI_COMM_WORLD, &num_process); // to get the number of process

	/*
	Ssend is blocking and also sychronous
	Where blocking is return from the Ssend once the sending window is available
	i.e. either passeed to the mem. or the link layer
	synchronous is to receive the notification from corresponding recv (handshake communication)
	*/

	if(task_rank == num_process - 1 && (num_process - 1) % 2 == 0){
		MPI_Ssend(&task_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); // last process(odd)
		MPI_Recv(&previous_task, 1, MPI_INT, task_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
	}
	else if(task_rank == num_process - 1 && (num_process - 1) % 2 == 1){
		MPI_Recv(&previous_task, 1, MPI_INT, task_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // last process(even)
		MPI_Ssend(&task_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else if(task_rank == 0){ 
		MPI_Ssend(&task_rank, 1, MPI_INT, task_rank + 1, 0, MPI_COMM_WORLD); // case process 0
		MPI_Recv(&previous_task, 1, MPI_INT, num_process - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
	}
	else if(task_rank % 2 == 0){
		MPI_Ssend(&task_rank, 1, MPI_INT, task_rank + 1, 0, MPI_COMM_WORLD); // odd
		MPI_Recv(&previous_task, 1, MPI_INT, task_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 	
	}
	else{
		MPI_Recv(&previous_task, 1, MPI_INT, task_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // even
		MPI_Ssend(&task_rank, 1, MPI_INT, task_rank + 1, 0, MPI_COMM_WORLD);	
	}

	std::cout << "I am task " << task_rank << ". My previous task is " << previous_task << "." << std::endl; //printing
	MPI_Finalize();

	return 0;
}
