#include "headerFiles/matrix_data_type.h"
#include "headerFiles/matrix_lib.h"
#include "headerFiles/file_reader.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>


int main(void){

    FILE* arq = fopen("matrix_exemplo.txt", "r");
    read_txt(arq);

    return 0;
}