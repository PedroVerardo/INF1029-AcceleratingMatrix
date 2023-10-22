#include "file_reader.h"
#include <stdlib.h>

Matrix* matrix_init(int height, int width){
    Matrix* new = (Matrix*)malloc(sizeof(Matrix));
    new->width = width;
    new->height = height;
    new->rows = (float*)aligned_alloc(32, sizeof(float)*new->height*new->width);
    
    return new;
}

void print_matrix_separation(int width)
{
    printf("\n ");
    for(int i=0; i < width; i++)
    {
        printf("----- ");
    }
}

void print_matrix(Matrix *matrix)
/*This is a simple function to print all elements of a matrix object,
for more information about matrix object look at file @matrix_data_type.h

    Args:
        matrix: A matrix object
    
    Returns:
        Nothing
*/
{
    for (int row = 0; row < matrix->height && row < 16; row++)
    {
        printf("\n|");
        for (int column = 0; column < matrix->width && column < 16; column++)
        {
            printf("%.2f |", matrix->rows[row*matrix->width + column]);
        }
        //print_matrix_separation(matrix->width);
    }
    printf("\n");
}

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