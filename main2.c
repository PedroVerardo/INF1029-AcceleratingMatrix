#include "headerFiles/matrix_data_type.h"
#include "headerFiles/matrix_lib.h"
#include "headerFiles/file_reader.h"
#include "headerFiles/time.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



int main(void){

    struct timeval start, stop, start2, stop2;

    // save_matrix_on_dat("matrixA.txt", "matrix_A.dat", 512, 512);
    // save_matrix_on_dat("matrixB.txt", "matrix_B.dat", 512, 512);

    Matrix* mA = read_matrix_dat("src/A_1024.dat", 1024, 1024);
    Matrix* mB = read_matrix_dat("src/B_1024.dat", 1024, 1024);
    
    Matrix* c = matrix_init(1024, 1024);
    Matrix* d = matrix_init(1024, 1024);


    print_matrix(mA);
    printf("\n\n");
    print_matrix(mB);

    gettimeofday(&start, NULL);
    matrix_matrix_mult(mA,mB, c);
    gettimeofday(&stop, NULL);

    print_matrix(c);
    printf("\nnormal time: %f ms\n", timedifference_msec(start, stop));

    gettimeofday(&start2, NULL);
    matrix_matrix_mult_optimized_vetorial(mA, mB, d);
    gettimeofday(&stop2, NULL);

    print_matrix(d);
    printf("\notimized time: %f ms\n", timedifference_msec(start2, stop2));

    return 0;
}