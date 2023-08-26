#ifndef _MARTIX_DATA_TYPE_H_
#define _MARTIX_DATA_TYPE_H_

struct matrix{
    unsigned long int width; 
    unsigned long int height;
    float *rows;
};

typedef struct matrix Matrix;

#endif /* _MARTIX_DATA_TYPE_H_ */