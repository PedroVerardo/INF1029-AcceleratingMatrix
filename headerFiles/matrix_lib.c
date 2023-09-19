/**************************************************************************************
* matrix_lib -- program to make matrix operations                                     *
*                                                                                     *                  
* Author: Pedro Lopes Verardo and Miguel Angelus                                      *
*                                                                                     *
* Prupose: Demonstrate how can matris operations can gain performance                 *
*           with different forms of programming them.                                 *
*                                                                                     *
* Usage: run the command make to test the gains of the matrix operations speed        *
*                                                                                     *
\**************************************************************************************/

#include "matrix_lib.h"

int matrix_mult_validations(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC){

    if(matrixA->height <= 0  || matrixA->width <= 0 || matrixB->height <= 0  || matrixB->width <= 0)
    {
        printf("Something wrong with your matrix width or height");
        return 0;
    }

    if(matrixA->width != matrixB->height)
    {
        printf("Inconsistent shapes matrixA have %ld width and matrixB have %ld height", matrixA->width, matrixB->height);
        return 0;
    }

    if(matrixC->height != matrixA->height || matrixC->width != matrixB->width)
    {
        printf("Inconsistent shape of resultant matrix the resultant have %ld width and %ld height", matrixA->height, matrixB->width);
        return 0;
    }

    return 1;
}

Matrix* matrix_init(int height, int width){
    Matrix* new = (Matrix*)malloc(sizeof(Matrix));
    new->width = width;
    new->height = height;
    new->rows = (float*)aligned_alloc(32, sizeof(float)*new->height*new->width);
    
    return new;
}

void print_matrix_separation(int width)
{
    printf("\n ");
    for(int i=0; i < width; i++)
    {
        printf("----- ");
    }
}

void print_matrix(Matrix *matrix)
/*This is a simple function to print all elements of a matrix object,
for more information about matrix object look at file @matrix_data_type.h

    Args:
        matrix: A matrix object
    
    Returns:
        Nothing
*/
{
    for (int row = 0; row < matrix->height && row < 16; row++)
    {
        printf("\n|");
        for (int column = 0; column < matrix->width && column < 16; column++)
        {
            printf("%.2f |", matrix->rows[row*matrix->width + column]);
        }
        //print_matrix_separation(matrix->width);
    }
    printf("\n");
}

int scalar_matrix_mult(float scalar_value, Matrix *matrix)
/*This function do a simple multiplication
    between a scalar and a matrix in the classical way

    Args: 
        scalar_value (float): A number to multiply the matrix

        matrix (Matrix): A matrix object to be multiplied, to see more about 
                        the matrix object look at file @matrix_data_type.h

    Returns:
        1: If matix is multiplied successfully
        0: If the operation failed, this don't verify if the float multiplication is bigger than a float
*/
{
    float value;
    if (matrix->height <= 0  || matrix->width <= 0)
    {
        printf("Something wrong with your matrix width or height");
        return 0;
    }

    for (int row = 0; row < matrix->height; row++)
    {
        for (int column = 0; column < matrix->width; column++)
        {
            value = matrix->rows[row*matrix->width + column];
            matrix->rows[row*matrix->width + column] = value*scalar_value;
        }
    }

    return 1;
}

int matrix_matrix_mult(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC)
{
    if(!matrix_mult_validations(matrixA, matrixB, matrixC)){
        puts("Invalid matrix format!\n");
        return 0;
    }

    for (int row = 0; row < matrixA->height; row++)
    {
        for (int columnB = 0; columnB < matrixB->width; columnB++)
        {
            for (int column = 0; column < matrixA->width; column++)
            {
                matrixC->rows[row*matrixC->width + columnB] += matrixA->rows[row*matrixA->width + column]
                *
                matrixB->rows[matrixB->width*column + columnB];
            }
        }
    }

    return 1;
}

int matrix_matrix_mult_optimized(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC)
{
    if(!matrix_mult_validations(matrixA, matrixB, matrixC)){
        puts("Invalid matrix format!\n");
        return 0;
    }

    int rowA, colA;
    int Cpos, Bpos;
    int qtdA = matrixA->height*matrixA->width;
    for(int elem = 0; elem < qtdA; elem++){
        colA = elem % matrixA->width;
        rowA = elem / matrixA->width;
        Cpos = rowA * matrixC->width;
        Bpos = colA * matrixB->width;
        for(int colB = 0; colB < matrixB->width; colB++){
            matrixC->rows[Cpos + colB] += matrixA->rows[elem] * matrixB->rows[Bpos + colB];
        }
        
    }

    return 1;
}

int matrix_matrix_mult_optimized_vetorial(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC)
{
    if(!matrix_mult_validations(matrixA, matrixB, matrixC)){
        puts("Invalid matrix format!\n");
        return 0;
    }

    int rowA, colA;
    int Cpos, Bpos;
    int qtdA = matrixA->height*matrixA->width;
    for(int elem = 0; elem < qtdA; elem++){
        colA = elem % matrixA->width;
        rowA = elem / matrixA->width;
        Cpos = rowA * matrixC->width;
        Bpos = colA * matrixB->width;
        for(int colB = 0; colB < matrixB->width; colB += 8){

            __m256 veca = _mm256_set1_ps(matrixA->rows[elem]);
            __m256 vecb = _mm256_load_ps(&matrixB->rows[Bpos + colB]);
            __m256 vecc = _mm256_load_ps(&matrixC->rows[Cpos + colB]);

            __m256 resultReg = _mm256_fmadd_ps(veca, vecb, vecc);

            _mm256_store_ps(&matrixC->rows[Cpos + colB], resultReg);
        }
        
    }

    return 1;
}