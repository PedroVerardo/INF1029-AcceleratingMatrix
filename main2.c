#include "headerFiles/matrix_data_type.h"
#include "headerFiles/matrix_lib.h"
#include "headerFiles/file_reader.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>


int main(void){

    save_matrix_on_dat("matrix_A.txt", "matrix_A.dat");
    save_matrix_on_dat("matrix_B.txt", "matrix_B.dat");

    Matrix* mA = read_matrix_dat("matrix_A.dat", 3, 2);
    Matrix* mB = read_matrix_dat("matrix_B.dat", 2, 2);
    
    Matrix* c = matrix_init(3, 2);
    // matrix_matrix_mult(mA,mB, c);
    // print_matrix(c);

    struct timeval start, stop, overall_t1, overall_t2;

    gettimeofday(&start, NULL);
    matrix_matrix_mult_optimized(mA, mB, c);
    gettimeofday(&stop, NULL);

    printf("Init time: %f ms\n", timedifference_msec(start, stop));
    print_matrix(c);

    return 0;
}