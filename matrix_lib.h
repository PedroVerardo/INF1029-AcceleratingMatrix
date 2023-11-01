#include "headerFiles/matrix_data_type.h"

int set_grid_size(int threads_per_block, int max_blocks_per_grid);
int scalar_matrix_mult_gpu(int tam,Matrix* mA,float* d_scalar,float* d_x);