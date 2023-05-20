#include <iostream>
#include <mpi.h>

/* this program is to practice the collective communication, to distribute the summation workload for the case of
1 master process and 3 slave processes. */

int main(int argc, char *argv[]){

    // to set up the chunk size
    const int chunk_size = 4;

    // start the mpi common world
    int num_process;
    int process_rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_process);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    // to set up the problem
    float send_buf[chunk_size][chunk_size];
    
    if(process_rank == 0){
        // master process: to allocate the workload
        for(int i = 0; i < chunk_size; i++){
            for(int j = 0; j < chunk_size; j++){
                send_buf[i][j] = i * 4 + j;
            }
        }
    }

    // to set up the receive buffer
    float receive_buf[chunk_size];

    // distribute the workload
    MPI_Scatter(send_buf, chunk_size, MPI_FLOAT, receive_buf, chunk_size, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // to do the workload
    float local_result = 0;
 
    // master & slave process: to do the workload
    for(int i = 0; i < chunk_size; i++){
        local_result += receive_buf[i];
    }

    // to gather the local result
    float final_result;
    MPI_Reduce(&local_result, &final_result, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    /* MPI_Reduce (&sendbuf,&recvbuf,count,datatype,op,root,comm) rem: root is the dest. */

    // to print the outcome
    if(process_rank == 0){
        std::cout << "The result is: " << final_result << std::endl;
    }

    MPI_Finalize();

    return 0;
}