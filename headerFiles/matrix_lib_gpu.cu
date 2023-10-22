__global__ 
void add(int n, float *d_x, float *d_y)
{
    for (int i = 0; i < n; ++i) {
    	d_y[i] = d_x[i] * d_y[i];
    }
}

__global__ 
void mult(int n, float value, float *d_y)
{
    for (int i = 0; i < n; ++i) {
    	d_y[i] = value * d_y[i];
    }
}

int scalar_matrix_mult_gpu(float scalar_value, Matrix *matrix)
{
    float value;
    if (matrix->height <= 0  || matrix->width <= 0)
    {
        printf("Something wrong with your matrix width or height");
        return 0;
    }

    int tam = matrix->height*matrix->width;
    for (int row = 0; row < tam; row++)
    {
        value = matrix->rows[];
        matrix->rows[] = value*scalar_value;

    }

    return 1;
}