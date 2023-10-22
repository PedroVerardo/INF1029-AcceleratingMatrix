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
    for (int i = 0; i < n; ++i) {
    	d_y[i] = d_x[i] * d_y[i];
    }
}

__global__ 
void mult(int n, float* value, float *d_y)
{
    for (int i = 0; i < n; ++i) {
    	d_y[i] = (*value) * d_y[i];
    }
}

// int scalar_matrix_mult_gpu(float scalar_value, Matrix *matrix)
// {
//     float value;
//     if (matrix->height <= 0  || matrix->width <= 0)
//     {
//         printf("Something wrong with your matrix width or height");
//         return 0;
//     }


//     int tam = matrix->height*matrix->width;
//     mult<<<1, 1>>>(tam, scalar_value, matrix->rows);
//     cudaDeviceSynchronize();
//     return 1;
// }



int main(int argc, char **argv){
    struct timeval start, stop, over_all_start, over_all_stop;
    float *d_x;
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
    
    printf("MATRIX A:\n");
    print_matrix(mA);
    printf("MATRIX B:\n");
    print_matrix(mB);

    //gpu
    int tam = mA->height*mA->width;
    cudaMalloc(&d_x, tam*sizeof(float));
    cudaMalloc(&d_scalar, sizeof(float));
    cudaMemcpy(d_scalar, &scalar, sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, mA->rows, tam*sizeof(float), cudaMemcpyHostToDevice);

    gettimeofday(&over_all_start, NULL);

    mult<<<1, 1>>>(tam, d_scalar, d_x);
    cudaDeviceSynchronize();

    gettimeofday(&over_all_stop, NULL);
    
    cudaMemcpy(mA->rows, d_x, tam*sizeof(float), cudaMemcpyDeviceToHost);

    printf("MATRIX A depois da multiplicacao:\n");
    print_matrix(mA);
    printf("\n");
    
    printf("Overall time: %f ms\n", timedifference_msec(over_all_start, over_all_stop));
    return 0;
}