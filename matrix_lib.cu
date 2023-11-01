
extern "C" {
    #include "headerFiles/matrix_data_type.h"
    #include "matrix_lib.h"
}

int THREAD_NUMBER_GPU =  256;
int THREAD_NUMBER_PER_GRID = 4096;

__global__ 
void mult(int n, float* value, float *d_y)
{
    int id = blockIdx.x*blockDim.x+threadIdx.x;
    int stride = gridDim.x*blockDim.x;
    // Make sure we do not go out of bounds
    for(int i = id; i < n; i+= stride){
        if(id < n){
            d_y[i] = (*value) * d_y[i];
        }
    }
}

int set_grid_size(int threads_per_block, int max_blocks_per_grid)
{
    if(threads_per_block == 0 || max_blocks_per_grid == 0)
    {
        return 0;
    }
    THREAD_NUMBER_GPU = threads_per_block;
    THREAD_NUMBER_PER_GRID = max_blocks_per_grid;
}

int scalar_matrix_mult_gpu(int tam,Matrix* mA,float* d_scalar,float* d_x)
{

    mult<<<THREAD_NUMBER_PER_GRID, THREAD_NUMBER_GPU>>>(tam, d_scalar, d_x);
    cudaDeviceSynchronize();
    
    cudaMemcpy(mA->rows, d_x, tam*sizeof(float), cudaMemcpyDeviceToHost);
}