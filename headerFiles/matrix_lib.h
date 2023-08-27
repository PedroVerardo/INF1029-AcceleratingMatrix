#ifndef _MARTIX_OPERATIONS_H_
#define _MARTIX_OPERATIONS_H_

#include "matrix_data_type.h"
#include <stdio.h>
#include <stdlib.h>

int scalar_matrix_mult(float scalar_value, Matrix *matrix);
int matrix_matrix_mult(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC);
void print_matrix(Matrix *matrix);
Matrix* matrix_init(int height, int width);

#endif /* _MARTIX_OPERATIONS_H_ */