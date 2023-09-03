#include "file_reader.h"
#include <stdlib.h>

FILE* openFile(const char* file, const char* mode)
{
    FILE* f = fopen(file, mode);
    if(f == NULL){
        perror("File opening error!");
    }
    return f;

}

Matrix* read_matrix_txt(FILE* file, int height, int width)
{
    Matrix * matrix;

    matrix = matrix_init(height, width);

    for(int i = 0; i < height*width; i++){
        fscanf(file, "%f ", &matrix->rows[i]);
    }

    return matrix;
}

void write_matrix_dat(FILE* file, Matrix* matrix)
{
    fwrite(matrix->rows, sizeof(float), matrix->width * matrix->height, file);
}

Matrix* read_matrix_dat(const char* file, int height, int width)
{
    FILE* fileDat = openFile(file, "rb");

    Matrix* m = matrix_init(height, width);
    fread(m->rows, sizeof(float), height * width, fileDat);
    return m;
}

Matrix* save_matrix_on_dat(const char* src, const char* dest, int width, int height)
/* src must be a .txt file that have dimensions and floats values for a matrix.
dest will be a binary file that has the floats of the txt matrix */
{
    FILE *fileDest, *fileSrc = openFile(src, "rb");
    Matrix* m = read_matrix_txt(fileSrc, height, width);

    fileDest = openFile(dest, "wb");
    write_matrix_dat(fileDest, m);

    fclose(fileSrc);
    fclose(fileDest);
    return m;
}