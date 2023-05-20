#include <iostream>
#include <mpi.h>

// This program is to investigate the different behaviours between blocking and non-blocking communication mode

int main(int argc, char *argv[]){
    // start the mpi common world
    MPI_Init(&argc, &argv);

    // get the task id
    int task_rank;
    MPI_Request request; // to handle non-blocking operation
    MPI_Comm_rank(MPI_COMM_WORLD, &task_rank);

    if(task_rank == 0){
        // master process
        int num_process;
        MPI_Comm_size(MPI_COMM_WORLD, &num_process);

        for(int i = 1; i < num_process; i++){
            MPI_Send(&i, 1, MPI_INT, i, 0, MPI_COMM_WORLD); // to distribute the work load by sending the array index
            /*rem. if i do the receive in the for loop, is not good for synchronous(Ssend), as I cant return from previous Ssend and 
                on the incrementation*/
        }

        for(int i = 1; i < num_process; i++){
            int recv_buf; // to receive the handled data from each slave process
            MPI_Recv(&recv_buf, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "The result of blocking: " << recv_buf << " from task " << i << std::endl;
        }
    }
    else{
        // slave process
        // to receive, handle and send back the data in each slave process
        int recv_buf;
        MPI_Recv(&recv_buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        recv_buf *= recv_buf;
        MPI_Send(&recv_buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if(task_rank == 0){
        // master process
        int num_process;
        MPI_Comm_size(MPI_COMM_WORLD, &num_process);

        for(int i = 1; i < num_process; i++){
            MPI_Isend(&i, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &request); // to distribute the work load by sending the array index
            /*rem. if i do the receive in the for loop, is not good for synchronous(Ssend), as I cant return from previous Ssend and 
                on the incrementation*/
        }

        for(int i = 1; i < num_process; i++){
            int recv_buf; // to receive the handled data from each slave process
            MPI_Irecv(&recv_buf, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &request);
            std::cout << "The result of non-blocking: " << recv_buf << " from task " << i << std::endl;
        }
    }
    else{
        // slave process
        // to receive, handle and send back the data in each slave process
        int recv_buf;
        MPI_Irecv(&recv_buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        recv_buf *= recv_buf;
        MPI_Isend(&recv_buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
    }

    MPI_Finalize();
    return 0;
}