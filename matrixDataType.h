struct Matrix {
    unsigned long int height;
    unsigned long int width;
    float *h_rows;
    float *d_rows;
    int alloc_mode;
};
typedef struct Matrix matrixGpu;