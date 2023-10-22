#include "matrix_lib.h"

FILE* openFile(const char* file, const char* mode);
Matrix* read_matrix_txt(FILE* file, int height, int width);
void write_matrix_dat(FILE* file, Matrix* matrix);
Matrix* read_matrix_dat(const char* file, int height, int width);
Matrix* save_matrix_on_dat(const char* src, const char* dest, int width, int height);
