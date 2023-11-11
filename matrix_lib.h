#include "headerFiles/matrix_data_type.h"

struct Matrix2 {
    unsigned long int height;
    unsigned long int width;
    float *h_rows;
    float *d_rows;
    int alloc_mode;
};
typedef struct Matrix2 matrixGpu;


int set_grid_size(int threads_per_block, int max_blocks_per_grid);
int scalar_matrix_mult_gpu(int tam,Matrix* mA,float d_scalar,float* d_x);
int matrix_matrix_mult_gpu(int tam, matrixGpu* d_mA, matrixGpu* d_mB, matrixGpu* d_mC);
int allocation_is_possible(int max_memory, matrixGpu* mA, matrixGpu* mB);
int matrix_matrix_mult_gpu(int tam, matrixGpu* mA, matrixGpu* mB, matrixGpu* mC);