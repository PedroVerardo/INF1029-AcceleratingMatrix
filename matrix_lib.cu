
extern "C" {
    #include "matrix_lib.h"
    #include <stdio.h>
}

int THREAD_NUMBER_GPU =  256;
int THREAD_NUMBER_PER_GRID = 4096;

__global__
void matrixMult(int n, float *d_matrixA, float *d_matrixB, float *d_matrixC, int tam)
{
    int colA;
    int Bpos;
    int id = blockIdx.x*blockDim.x+threadIdx.x;
    int stride = gridDim.x*blockDim.x;
    if(id < n){
        for(int i = id; i < n; i+= stride){
            colA = i % tam;
            Bpos = colA * tam;
            
            for(int colB = 0; colB < tam; colB++){
                d_matrixC[i] += d_matrixA[i] * d_matrixB[Bpos + colB];
            }
        }
    }
    
}

__global__ 
void mult(int n, float value, float *d_y)
{
    int id = blockIdx.x*blockDim.x+threadIdx.x;
    int stride = gridDim.x*blockDim.x;
    // Make sure we do not go out of bounds
    for(int i = id; i < n; i+= stride){
        if(id < n){
            d_y[i] = (value) * d_y[i];
        }
    }
}

int set_grid_size(int threads_per_block, int max_blocks_per_grid)
{
    if(threads_per_block == 0 || max_blocks_per_grid == 0)
    {
        return 0;
    }
    else if(threads_per_block > 1024 || max_blocks_per_grid > 65535 )
    {
        return 0;
    }
    THREAD_NUMBER_GPU = threads_per_block;
    THREAD_NUMBER_PER_GRID = max_blocks_per_grid;

    printf("numero de threads: %d\n", THREAD_NUMBER_GPU);
    return 1;
}

int scalar_matrix_mult_gpu(int tam, matrixGpu* mA, float d_scalar)
{

    mult<<<THREAD_NUMBER_PER_GRID, THREAD_NUMBER_GPU>>>(tam, d_scalar, mA->d_rows);
    cudaError_t error = cudaDeviceSynchronize();
    if(error)
    {
        return 0;
    }
    
    error = cudaMemcpy(mA->h_rows, mA->d_rows, tam*sizeof(float), cudaMemcpyDeviceToHost);
    if(error)
    {
        return 0;
    }
    return 1;
}

int matrix_matrix_mult_gpu(int tam, matrixGpu* mA, matrixGpu* mB, matrixGpu* mC)
{
    matrixMult<<<THREAD_NUMBER_PER_GRID, THREAD_NUMBER_GPU>>>(tam, mA->d_rows, mB->d_rows, mC->d_rows, mC->width);
    // cudaError_t error = cudaDeviceSynchronize();
    // if(error)
    // {
    //     return 0;
    // }
    
    return 1;
}

int allocation_is_possible(int max_memory, matrixGpu* mA, matrixGpu* mB)
{
    long long bytes = max_memory * 1000000;
    int partial_allocation_tot = (mB->height*mB->width + mA->width + mB->height)*4;
    int allocation_tot = (mB->height*mB->width + mA->width*mA->height + mA->height*mB->width)*4;
    if(bytes > allocation_tot)
    {
        return FULL_ALLOC;
    }

    else if(bytes > partial_allocation_tot)
    {
        return PARTIAL_ALLOC;
    }

    else
    {
        printf("The matrix multiplication with this memory is insufficient! Please make available more memory.");
        exit(1);
    }
}