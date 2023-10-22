#ifndef _MARTIX_OPERATIONS_H_
#define _MARTIX_OPERATIONS_H_

#include "matrix_data_type.h"
#include <stdio.h>
#include <stdlib.h>
//#include <immintrin.h>
#include <pthread.h>

int matrix_mult_validations(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC);
int scalar_matrix_mult(float scalar_value, Matrix *matrix);
int matrix_matrix_mult(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC);
int matrix_matrix_mult_optimized(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC);
//int matrix_matrix_mult_optimized_vetorial(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC);
//int scalar_matrix_mult_optimized_vetorial(float scalar_value, Matrix *matrix);
//int matrix_matrix_mult_optimized_vetorial_with_threads(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC);
void print_matrix(Matrix *matrix);
//void set_number_threads(int num_threads);
//int scalar_matrix_thread_mult(float scalar_value, struct matrix *matrix);
Matrix* matrix_init(int height, int width);
int check_matrix(Matrix* matrix, float result);

#endif /* _MARTIX_OPERATIONS_H_ */