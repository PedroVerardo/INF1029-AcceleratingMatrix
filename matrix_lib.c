#include "matrix_lib.h"

matrixGpu* matrix_init(int height, int width){
    matrixGpu* n = (matrixGpu*)malloc(sizeof(matrixGpu));
    n->width = width;
    n->height = height;
    n->h_rows = (float*)malloc(sizeof(float)*n->height*n->width);
    n->d_rows = NULL;
    
    return n;
}

FILE* openFile(const char* file, const char* mode)
{
    FILE* f = fopen(file, mode);
    if(f == NULL){
        perror("File opening error!");
    }
    return f;

}

matrixGpu* read_matrix_txt(FILE* file, int height, int width)
{
    matrixGpu * matrix;

    matrix = matrix_init(height, width);

    for(int i = 0; i < height*width; i++){
        fscanf(file, "%f ", &matrix->h_rows[i]);
    }

    return matrix;
}

void write_matrix_dat(FILE* file, matrixGpu* matrix)
{
    fwrite(matrix->h_rows, sizeof(float), matrix->width * matrix->height, file);
}

matrixGpu* read_matrix_dat(const char* file, int height, int width)
{
    FILE* fileDat = openFile(file, "rb");

    matrixGpu* m = matrix_init(height, width);
    fread(m->h_rows, sizeof(float), height * width, fileDat);
    return m;
}

matrixGpu* save_matrix_on_dat(const char* src, const char* dest, int width, int height)
/* src must be a .txt file that have dimensions and floats values for a matrix.
dest will be a binary file that has the floats of the txt matrix */
{
    FILE *fileDest, *fileSrc = openFile(src, "rb");
    matrixGpu* m = read_matrix_txt(fileSrc, height, width);

    fileDest = openFile(dest, "wb");
    write_matrix_dat(fileDest, m);

    fclose(fileSrc);
    fclose(fileDest);
    return m;
}

void print_matrix_separation(int width)
{
    printf("\n ");
    for(int i=0; i < width; i++)
    {
        printf("----- ");
    }
}

void print_matrix(matrixGpu *matrix)
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
            printf("%.2f |", matrix->h_rows[row*matrix->width + column]);
        }
        //print_matrix_separation(matrix->width);
    }
    printf("\n");
}