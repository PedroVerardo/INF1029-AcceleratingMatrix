
extern "C" {
    #include "headerFiles/matrix_data_type.h"
    #include "matrix_lib.h"
    #include <stdio.h>
}

int THREAD_NUMBER_GPU =  256;
int THREAD_NUMBER_PER_GRID = 4096;

__global__
void matrixMult(int n, float *d_matrixA, float *d_matrixB, float *d_matrixC, int tam)
{
    int rowA, colA;
    int Cpos, Bpos;
    int id = blockIdx.x*blockDim.x+threadIdx.x;
    int row=blockIdx.x*blockDim.x+threadIdx.x;
    int col=blockIdx.y*blockDim.y+threadIdx.y;
    int stride = gridDim.x*blockDim.x;
    
    for(int i = id; i < n; i+= stride){
        colA = i % tam;
        rowA = i / tam;
        Cpos = rowA * tam;
        Bpos = colA * tam;
        
        // for(int colB = 0; colB < tam; colB++){
        //     d_matrixC[Cpos + colB] += d_matrixA[i] * d_matrixB[Bpos + colB];
        // }
        for(int colB = 0; colB < tam; colB++){
            d_matrixC[i] += d_matrixA[i] * d_matrixB[Bpos + colB];
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
    return 1;
}

int scalar_matrix_mult_gpu(int tam,Matrix* mA,float d_scalar,float* d_x)
{

    mult<<<THREAD_NUMBER_PER_GRID, THREAD_NUMBER_GPU>>>(tam, d_scalar, d_x);
    cudaError_t error = cudaDeviceSynchronize();
    if(error)
    {
        return 0;
    }
    
    error = cudaMemcpy(mA->rows, d_x, tam*sizeof(float), cudaMemcpyDeviceToHost);
    if(error)
    {
        return 0;
    }
    return 1;
}

int matrix_matrix_mult_gpu(int tam, matrixGpu* mA, matrixGpu* mB, matrixGpu* mC)
{
    matrixMult<<<THREAD_NUMBER_PER_GRID, THREAD_NUMBER_GPU>>>(tam, mA->d_rows, mB->d_rows, mC->d_rows, mC->width);
    cudaError_t error = cudaDeviceSynchronize();
    if(error)
    {
        return 0;
    }
    
    error = cudaMemcpy(mC->rows, mC->d_rows, tam*sizeof(float), cudaMemcpyDeviceToHost);
    if(error)
    {
        return 0;
    }
    return 1;
}

int allocation_is_possible(int max_memory, matrixGpu* mA, matrixGpu* mB)
{
    int partial_allocation_tot = (mB->height*mB->width + mA->width + mB->height)*4;
    int allocation_tot = (mB->height*mB->width + mA->width*mA->height + mA->height*mB->width)*4;
    if(max_memory > allocation_tot)
    {
        return 1;
    }

    else if(max_memory > partial_allocation_tot)
    {
        return 0;
    }

    else
    {
        printf("The matrix multiplication with this memory is insufficient! Please make available more memory.");
        exit(1);
    }
}