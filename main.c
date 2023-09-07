#include "headerFiles/matrix_data_type.h"
#include "headerFiles/matrix_lib.h"
#include "headerFiles/file_reader.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    save_matrix_on_dat("src/A_1024.txt", "src/A_1024.dat", 1024, 1024);
    save_matrix_on_dat("src/B_1024.txt", "src/B_1024.dat", 1024, 1024);

    save_matrix_on_dat("src/A_2048.txt", "src/A_2048.dat", 2048, 2048);
    save_matrix_on_dat("src/B_2048.txt", "src/B_2048.dat", 2048, 2048);

    return 0;
}