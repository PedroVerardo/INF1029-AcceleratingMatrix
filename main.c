#include "headerFiles/matrix_data_type.h"
#include "headerFiles/matrix_lib.h"
#include "headerFiles/file_reader.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    Matrix* a = read_matrix_dat("src/result1.dat", 512, 512);
    Matrix* b = read_matrix_dat("src/result2.dat", 512, 512);
    
    print_matrix(a);
    printf("\n");
    print_matrix(b);

    return 0;
}