#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define FULL_ALLOC 1
#define PARTIAL_ALLOC 0

struct Matrix2 {
    unsigned long int height;
    unsigned long int width;
    float *h_rows;
    float *d_rows;
    int alloc_mode;
};
typedef struct Matrix2 matrixGpu;

int set_grid_size(int threads_per_block, int max_blocks_per_grid);
int scalar_matrix_mult_gpu(int tam, matrixGpu* mA, float d_scalar);
int matrix_matrix_mult_gpu(int tam, matrixGpu* d_mA, matrixGpu* d_mB, matrixGpu* d_mC);
int allocation_is_possible(int max_memory, matrixGpu* mA, matrixGpu* mB);
int matrix_matrix_mult_gpu(int tam, matrixGpu* mA, matrixGpu* mB, matrixGpu* mC);
matrixGpu* matrix_init(int height, int width);
FILE* openFile(const char* file, const char* mode);
matrixGpu* read_matrix_txt(FILE* file, int height, int width);
void write_matrix_dat(FILE* file, matrixGpu* matrix);
matrixGpu* read_matrix_dat(const char* file, int height, int width);
matrixGpu* save_matrix_on_dat(const char* src, const char* dest, int width, int height);
void print_matrix(matrixGpu *matrix);
