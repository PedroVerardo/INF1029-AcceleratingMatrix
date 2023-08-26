#include "headerFiles/matrix_data_type.h"
#include "headerFiles/matrix_lib.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    Matrix *a = (Matrix*)malloc(sizeof(Matrix));
    a->width = 3;
    a->height = 2;
    a->rows = (float*)malloc(sizeof(float)*a->height*a->width);
    a->rows[0] = 1;
    a->rows[1] = 2;
    a->rows[2] = 3;
    a->rows[3] = 4;
    a->rows[4] = 5;
    a->rows[5] = 6;

    Matrix *b = (Matrix*)malloc(sizeof(Matrix));
    b->width = 2;
    b->height = 3;
    b->rows = (float*)malloc(sizeof(float)*b->height*b->width);

    b->rows[0] = 1;
    b->rows[1] = 2;
    b->rows[2] = 3;
    b->rows[3] = 4;
    b->rows[4] = 5;
    b->rows[5] = 6;

    Matrix *c = (Matrix*)malloc(sizeof(Matrix));
    c->width = 2;
    c->height = 2;
    c->rows = (float*)malloc(sizeof(float)*c->height*c->width);
    
    //print_matrix(a);
    print_matrix(b);

    scalar_matrix_mult(2.0f, b);

    print_matrix(b);

    //matrix_matrix_mult(a,b,c);

    //print_matrix(c);

    free(a->rows);
    free(a);
    free(b->rows);
    free(b);
    free(c->rows);
    free(c);
}