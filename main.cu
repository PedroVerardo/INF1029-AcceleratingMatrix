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
}

__global__ 
void add(int n, float *d_x, float *d_y)
{
}

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

__global__
void matrixMult(int n, float *d_matrixA, float *d_matrixB, float *d_matrixC, int tam)
{
    int rowA, colA;
    int Cpos, Bpos;

    int id = blockIdx.x*blockDim.x+threadIdx.x;

    colA = id % tam;
    rowA = id / tam;
    Cpos = rowA * tam;
    Bpos = colA * tam;
    for(int colB = 0; colB < tam; colB++){
         d_matrixC[Cpos + colB] += d_matrixA[id] * d_matrixB[Bpos + colB];
    }
}


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
    int num_threads = atoi(argv[6]);
    char* input_matrix_a = argv[7];
    char* input_matrix_b = argv[8];
    char* output_matrix_a = argv[9];
    char* output_matrix_b = argv[10];
    
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
    cudaMalloc(&d_scalar, sizeof(float));
    cudaMemcpy(d_scalar, &scalar, sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, mA->rows, tamA*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, mB->rows, tamB*sizeof(float), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int gridSize = 4096;

    gettimeofday(&over_all_start, NULL);

    mult<<<gridSize, blockSize>>>(tamA, d_scalar, d_x);
    cudaDeviceSynchronize();

    gettimeofday(&over_all_stop, NULL);
    
    cudaMemcpy(mA->rows, d_x, tamA*sizeof(float), cudaMemcpyDeviceToHost);

    matrixMult<<<gridSize, blockSize>>>(tamC, d_x, d_y, d_c, tamC);
    cudaDeviceSynchronize();

    cudaMemcpy(mC->rows, d_c, tamC*sizeof(float), cudaMemcpyDeviceToHost);

    printf("MATRIX A depois da multiplicacao:\n");
    print_matrix(mA);
    printf("\n");
    
    printf("MATRIX C depois da multiplicacao:\n");
    print_matrix(mC);
    printf("\n");

    printf("Overall time: %f ms\n", timedifference_msec(over_all_start, over_all_stop));

    cudaFree(d_x);
    cudaFree(d_y);
    cudaFree(d_c);
    cudaFree(d_scalar);
    return 0;
}