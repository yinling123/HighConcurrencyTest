#include<mpi.h>
#include<iostream>

int main(){
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    //获取当前的排名
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    //获取当前进程的名字，即主机名
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len; 
    MPI_Get_processor_name(processor_name, &name_len);

    // MPI_Barrier(MPI_COMM_WORLD);
    
    // std::cout << "hello world from processor " << processor_name << "," << "rank " << world_rank << "out of " << world_size << "processors " << std::endl;
    
    printf("hello world from processor processor_name %s, rank world_rank %d out of %d\n", processor_name, world_rank, world_size);

    MPI_Finalize();
    return 0;
}