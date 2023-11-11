#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cpuid.h>
extern "C" {
#include "headerFiles/time.h"
#include "matrix_lib.h"
}

int main(int argc, char **argv){
    struct timeval start, stop, over_all_start, over_all_stop;
    
    gettimeofday(&over_all_start, NULL);
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
    
    matrixGpu* mA = read_matrix_dat(input_matrix_a, widith_a, height_a);
    matrixGpu* mB = read_matrix_dat(input_matrix_b, width_b, height_b);
    matrixGpu* mC = matrix_init(height_a, width_b);

    int allocation_type = allocation_is_possible(num_max_memory, mA, mB);
    mA->alloc_mode = allocation_type;
    mC->alloc_mode = allocation_type;
    mB->alloc_mode = FULL_ALLOC;

    printf("Allocation type selected: %s\n", allocation_type == FULL_ALLOC ? "full allocation" : "partial allocation");
    
    printf("MATRIX A:\n");
    print_matrix(mA);
    printf("MATRIX B:\n");
    print_matrix(mB);

    int blockSize = 256;
    int gridSize = 4096;
    int tamA = mA->height*mA->width;
    int tamB = mB->height*mB->width;
    int tamC = mC->height*mC->width;

    // scalar multi
    cudaMalloc(&mA->d_rows, sizeof(float) * tamA);
    cudaMemcpy(mA->d_rows, mA->h_rows, sizeof(float) * tamA, cudaMemcpyHostToDevice);
    scalar_matrix_mult_gpu(tamA, mA, scalar);

    printf("MATRIX AFTER SCALAR MULTIPLICATION:\n");
    print_matrix(mA);

    // matrix multi 
    gettimeofday(&start, NULL);
    cudaMalloc(&mB->d_rows, sizeof(float) * tamB);
    cudaMemcpy(mB->d_rows, mB->h_rows, sizeof(float) * tamB, cudaMemcpyHostToDevice);
    if(allocation_type == FULL_ALLOC){
        cudaMalloc(&mA->d_rows, sizeof(float) * tamA);
        cudaMalloc(&mC->d_rows, sizeof(float) * tamC);
        cudaMemcpy(mA->d_rows, mA->h_rows, sizeof(float) * tamA, cudaMemcpyHostToDevice);
        cudaMemcpy(mC->d_rows, mC->h_rows, sizeof(float) * tamC, cudaMemcpyHostToDevice);
        matrix_matrix_mult_gpu(tamA, mA, mB, mC);
        cudaMemcpy(mC->h_rows, mC->d_rows, sizeof(float) * tamC, cudaMemcpyDeviceToHost);
    }
    else{
        cudaMalloc(&mA->d_rows, sizeof(float) * mA->width);
        cudaMalloc(&mC->d_rows, sizeof(float) * mC->width);
        for(int i = 0; i < mA->height; i++){
            cudaMemcpy(mA->d_rows, mA->h_rows + i*mA->width, sizeof(float) * mA->width, cudaMemcpyHostToDevice);
            cudaMemcpy(mC->d_rows, mC->h_rows + i*mC->width, sizeof(float) * mC->width, cudaMemcpyHostToDevice);
            matrix_matrix_mult_gpu(mA->width, mA, mB, mC);
            cudaMemcpy(mC->h_rows + i * mC->width, mC->d_rows, sizeof(float) * mC->width, cudaMemcpyDeviceToHost);
        }
        
    }
    gettimeofday(&stop, NULL);
    printf("Multiplication time: %f ms with %s allocation\n", 
            timedifference_msec(start, stop), allocation_type == FULL_ALLOC ? "full" : "partial");


    printf("MATRIX A depois da multiplicacao:\n");
    print_matrix(mC);
    printf("\n");

    gettimeofday(&over_all_stop, NULL);

    printf("Overall time: %f ms\n", timedifference_msec(over_all_start, over_all_stop));

    return 0;
}