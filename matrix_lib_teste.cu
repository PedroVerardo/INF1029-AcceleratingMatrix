#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cpuid.h>
extern "C" {
#include "timer.h"
#include "headerFiles/matrix_data_type.h"
#include "headerFiles/file_reader.h"
#include "matrix_lib.h"
}

// __global__ 
// void mult(int n, float* value, float *d_y)
// {
//     int id = blockIdx.x*blockDim.x+threadIdx.x;
//     int stride = gridDim.x*blockDim.x;
//     // Make sure we do not go out of bounds
//     for(int i = id; i < n; i+= stride){
//         if(id < n){
//             d_y[i] = (*value) * d_y[i];
//         }
//     }
// }

// __global__
// void matrixMult(int n, float *d_matrixA, float *d_matrixB, float *d_matrixC, int tam)
// {
//     int rowA, colA;
//     int Cpos, Bpos;
//     int id = blockIdx.x*blockDim.x+threadIdx.x;
//     int row=blockIdx.x*blockDim.x+threadIdx.x;
//     int col=blockIdx.y*blockDim.y+threadIdx.y;
//     int stride = gridDim.x*blockDim.x;
    
//     for(int i = id; i < n; i+= stride){
//         colA = i % tam;
//         rowA = i / tam;
//         Cpos = rowA * tam;
//         Bpos = colA * tam;
        
//         // for(int colB = 0; colB < tam; colB++){
//         //     d_matrixC[Cpos + colB] += d_matrixA[i] * d_matrixB[Bpos + colB];
//         // }
//         for(int colB = 0; colB < tam; colB++){
//             d_matrixC[i] += d_matrixA[i] * d_matrixB[Bpos + colB];
//         }
//     }
// }


int main(int argc, char **argv){
    struct timeval start, stop, over_all_start, over_all_stop;
    float *d_x;
    float *d_y;
    float *d_c;
    float *d_scalar;
    
    const float scalar = atof(argv[1]);
    int widith_a = atoi(argv[2]);
    int height_a = atoi(argv[3]);
    int width_b = atoi(argv[4]);
    int height_b = atoi(argv[5]);
    int num_threads_block = atoi(argv[6]);
    int num_block_grid = atoi(argv[7]);
    int num_max_memory = atoi(argv[8]);
    char* input_matrix_a = argv[9];
    char* input_matrix_b = argv[10];
    char* output_matrix_a = argv[11];
    char* output_matrix_b = argv[12];
    
    Matrix* mA = read_matrix_dat(input_matrix_a, widith_a, height_a);
    Matrix* mB = read_matrix_dat(input_matrix_b, width_b, height_b);
    Matrix* mC = matrix_init(height_a, width_b);
    
    printf("MATRIX A:\n");
    print_matrix(mA);
    printf("MATRIX B:\n");
    print_matrix(mB);

    //gpu
    int tamA = mA->height*mA->width;
    int tamB = mB->height*mB->width;
    int tamC = mC->height*mC->width;

    cudaMalloc(&d_x, tamA*sizeof(float));
    cudaMalloc(&d_y, tamB*sizeof(float));
    cudaMalloc(&d_c, tamC*sizeof(float));
    cudaMemcpy(d_x, mA->rows, tamA*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, mB->rows, tamB*sizeof(float), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int gridSize = 4096;

    scalar_matrix_mult_gpu(tamA, mA, scalar, d_x);

    printf("MATRIX A depois da multiplicacao:\n");
    print_matrix(mA);
    printf("\n");

    // matrixMult<<<gridSize, blockSize>>>(tamC, d_x, d_y, d_c, 2048);
    // cudaDeviceSynchronize();

    // cudaMemcpy(mC->rows, d_c, tamC*sizeof(float), cudaMemcpyDeviceToHost);
    
    // printf("MATRIX C depois da multiplicacao:\n");
    // print_matrix(mC);
    // printf("\n");

    //printf("Overall time: %f ms\n", timedifference_msec(over_all_start, over_all_stop));

    cudaFree(d_x);
    cudaFree(d_y);
    cudaFree(d_c);
    cudaFree(d_scalar);
    return 0;
}