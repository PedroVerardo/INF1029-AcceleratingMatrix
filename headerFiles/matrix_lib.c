/**************************************************************************************
* matrix_lib -- program to make matrix operations                                     *
*                                                                                     *                  
* Author: Pedro Lopes Verardo and Miguel Angelus                                      *
*                                                                                     *
* Prupose: Demonstrate how can matris operations can gain performance                 *
*           with different forms of programming them.                                 *
*                                                                                     *
* Usage: run the command make ----- to test the gains of the matrix operations speed  *
*                                                                                     *
\**************************************************************************************/

#include "matrix_lib.h"

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
    for (int row = 0; row < matrix->height; row++)
    {
        printf("\n|");
        for (int column = 0; column < matrix->width; column++)
        {
            printf("%.2f |", matrix->rows[row*matrix->width + column]);
        }
        print_matrix_separation(matrix->width);
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
    float sum;

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

    if(matrixC->width != matrixA->height || matrixC->height != matrixB->width)
    {
        printf("Inconsistent shape of resultant matrix the resultant have %ld width and %ld height", matrixA->height, matrixB->width);
        return 0;
    }

    for (int row = 0; row < matrixA->height; row++)
    {
        for (int columnB = 0; columnB < matrixB->width; columnB++)
        {
            sum = 0;
            for (int column = 0; column < matrixA->width; column++)
            {
                sum += matrixA->rows[row*matrixA->width + column]*matrixB->rows[matrixB->width*column + columnB];
            }
            matrixC->rows[row*matrixC->width + columnB] = sum;
        }
    }

    return 1;
}