#include "headerFiles/matrix_data_type.h"
#include "headerFiles/matrix_lib.h"
#include "headerFiles/file_reader.h"
#include "headerFiles/time.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MATRIX_TAM 1024



int main(void){

    struct timeval start, stop, start2, stop2;

    // save_matrix_on_dat("matrixA.txt", "matrix_A.dat", 512, 512);
    // save_matrix_on_dat("matrixB.txt", "matrix_B.dat", 512, 512);

    Matrix* mA = read_matrix_dat("src/A_1024.dat", MATRIX_TAM, MATRIX_TAM);
    Matrix* mB = read_matrix_dat("src/B_1024.dat", MATRIX_TAM, MATRIX_TAM);
    
    Matrix* c = matrix_init(MATRIX_TAM, MATRIX_TAM);
    Matrix* d = matrix_init(MATRIX_TAM, MATRIX_TAM);

    printf("---------------------------Matrix A---------------------------\n");
    print_matrix(mA);
    printf("\n\n");
    printf("---------------------------Matrix B---------------------------\n");
    print_matrix(mB);

    printf("---------------------------Matrix A after scalar multiplication---------------------------\n");
    //falta mostrar o resultado escalar aqui

    printf("---------------------------Multiplicacao nao otimizada---------------------------\n");
    gettimeofday(&start, NULL);
    matrix_matrix_mult(mA,mB, c);
    gettimeofday(&stop, NULL);

    print_matrix(c);
    printf("\nnormal time: %f ms\n", timedifference_msec(start, stop));
    printf("---------------------------Multiplicacao linearmente otimizada---------------------------\n");
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

    //escrita do resultado
    

    return 0;
}