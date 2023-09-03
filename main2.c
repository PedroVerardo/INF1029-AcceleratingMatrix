#include "headerFiles/matrix_data_type.h"
#include "headerFiles/matrix_lib.h"
#include "headerFiles/file_reader.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>


int main(void){

    struct timeval start, stop, start2, stop2;

    save_matrix_on_dat("matrixA.txt", "matrix_A.dat", 512, 512);
    save_matrix_on_dat("matrixB.txt", "matrix_B.dat", 512, 512);

    Matrix* mA = read_matrix_dat("matrix_A.dat", 512, 512);
    Matrix* mB = read_matrix_dat("matrix_B.dat", 512, 512);
    
    Matrix* c = matrix_init(512, 512);
    Matrix* d = matrix_init(512, 512);

    gettimeofday(&start, NULL);
    matrix_matrix_mult(mA,mB, d);
    gettimeofday(&stop, NULL);

    printf("Init time: %ld ms\n", stop.tv_usec - start.tv_usec);
    print_matrix(d);

    gettimeofday(&start2, NULL);
    matrix_matrix_mult_optimized(mA, mB, c);
    gettimeofday(&stop2, NULL);

    printf("Init time: %ld ms\n", stop2.tv_usec - start2.tv_usec);
    print_matrix(c);

    return 0;
}