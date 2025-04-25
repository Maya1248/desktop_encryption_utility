#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/AES_256_ECB.h"

#endif

int is_writable(char *file_name) {
    FILE *temp_fptr = fopen(file_name, "rb+");

    if (temp_fptr != NULL) {
        fclose(temp_fptr);
        return 0;
    }
    return 1;
}

