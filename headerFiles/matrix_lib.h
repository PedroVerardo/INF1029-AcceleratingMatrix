#ifndef _MARTIX_OPERATIONS_H_
#define _MARTIX_OPERATIONS_H_

#include "matrix_data_type.h"
#include <stdio.h>

int scalar_matrix_mult(float scalar_value, Matrix *matrix);
int matrix_matrix_mult(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC);
void print_matrix(Matrix *matrix);

#endif /* _MARTIX_OPERATIONS_H_ */