#include "file_reader.h"
#include <stdlib.h>

void read_txt(FILE* file){
    int height, width;
    Matrix * matrix;

    if(fscanf(file, "%d %d\n", &height, &width) != 2){
        printf("Invalid file format!");
        return;
    }

    matrix = matrix_init(height, width);

    for(int i = 0; i < height*width; i++){
        fscanf(file, "%f ", &matrix->rows[i]);
    }
    print_matrix(matrix);
}