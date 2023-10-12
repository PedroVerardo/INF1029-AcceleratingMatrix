#ifndef _MARTIX_DATA_TYPE_H_
#define _MARTIX_DATA_TYPE_H_

struct matrix{
    unsigned long int width; 
    unsigned long int height;
    float *rows;
};

typedef struct matrix Matrix;

struct matrix_multiply{
    int final;
    int ini;
    float scalar;
    Matrix* A;
    Matrix* B;
    Matrix* C;
};
typedef struct matrix_multiply Mmult;

#endif /* _MARTIX_DATA_TYPE_H_ */