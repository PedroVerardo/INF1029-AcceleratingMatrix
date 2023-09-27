#include "headerFiles/matrix_data_type.h"
#include "headerFiles/matrix_lib.h"
#include "headerFiles/file_reader.h"
#include "headerFiles/time.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cpuid.h>

int main(int argc, char **argv){
    
    struct timeval start, stop, over_all_start, over_all_stop;
    gettimeofday(&over_all_start, NULL);

    float scalar = atof(argv[1]);
    int widith_a = atoi(argv[2]);
    int height_a = atoi(argv[3]);
    int width_b = atoi(argv[4]);
    int height_b = atoi(argv[5]);
    char* input_matrix_a = argv[6];
    char* input_matrix_b = argv[7];
    char* output_matrix_a = argv[8];
    char* output_matrix_b = argv[9];

    //system("cat /proc/cpuinfo");

    Matrix* mA = read_matrix_dat(input_matrix_a, widith_a, height_a);
    Matrix* mB = read_matrix_dat(input_matrix_b, width_b, height_b);
    
    Matrix* mC = matrix_init(height_a, width_b);
    Matrix* mD = matrix_init(height_a, width_b);
    Matrix* mE = matrix_init(height_a, width_b);
    Matrix* mF = matrix_init(height_a, width_b);

    printf("MATRIX A:\n");
    print_matrix(mA);
    printf("MATRIX B:\n");
    print_matrix(mB);

    scalar_matrix_mult_optimized_vetorial(scalar, mA);
    printf("MATRIX A depois da multiplicacao:\n");
    print_matrix(mA);
    printf("\n");
    //write_matrix_dat(openFile(output_matrix_a, "wb"), mA);

    // standart matrix multiplication algorithm
    // gettimeofday(&start, NULL);
    // matrix_matrix_mult(mA, mB, mC);
    // gettimeofday(&stop, NULL);

    //print_matrix(mC);
    //printf("\nMultiplication time: %f ms\n", timedifference_msec(start, stop));
    //

    // optimized algorithm
    // gettimeofday(&start, NULL);
    // matrix_matrix_mult_optimized(mA, mB, mD);
    // gettimeofday(&stop, NULL);

    // print_matrix(mD);
    // write_matrix_dat(openFile(output_matrix_b, "wb"), mD);
    // printf("\nMultiplication linearity optimization time: %f ms\n", timedifference_msec(start, stop));
    

    //optimized algorithm with vector instructions
//     gettimeofday(&start, NULL);
//     matrix_matrix_mult_optimized_vetorial(mA, mB, mE);
//     gettimeofday(&stop, NULL);

//     print_matrix(mE);
//     printf("Multiplication linearity optimization with vector instructions time: %f ms\n", 
//             timedifference_msec(start, stop));

    gettimeofday(&start, NULL);
    matrix_matrix_mult_optimized_vetorial_with_threads(24, mA, mB, mF);
    gettimeofday(&stop, NULL);

    print_matrix(mF);
    printf("Multiplication THREAD optimization with vector instructions time: %f ms\n", 
            timedifference_msec(start, stop));
    //write_matrix_dat(openFile(output_matrix_b, "wb"), mE);
    
    

    gettimeofday(&over_all_stop, NULL);
    printf("Overall time: %f ms\n", timedifference_msec(over_all_start, over_all_stop));

    return 0;
}