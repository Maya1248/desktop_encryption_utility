#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/AES_256_ECB.h"
#include "../lib/SHA_256.h"

#endif

int is_writable(char *file_name) {
    FILE *temp_fptr = fopen(file_name, "rb+");

    if (temp_fptr != NULL) {
        fclose(temp_fptr);
        return 0;
    }
    return 1;
}

long long get_file_size(char *relative_name) {
    FILE *fptr = fopen(relative_name, "rb");

    fseek(fptr, 0, SEEK_END);
    long long file_size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    fclose(fptr);

    return file_size;
}

int hasEnc(char *file_name) {
    int index = strlen(file_name) - 1;
    if (file_name[index - 3] == '.' && file_name[index - 2] == 'e' && file_name[index - 1] == 'n' && file_name[index] == 'c') {
        return 0;
    }

    return -1;
}

int check_password(char *password_string, char *file_name) {
    FILE *fptr = fopen(file_name, "rb+");
    unsigned char *password_hash = hash(password_string);
    unsigned char password_hash_buffer[32];

    fread(password_hash_buffer, sizeof(unsigned char), 32, fptr);
    for (int i = 0; i < 32; i++) {
        if (password_hash[i] != password_hash_buffer[i]) {
            free(password_hash);
            fclose(fptr);
            return 1;
        }
    }

    free(password_hash);
    fclose(fptr);
    return 0;
}

void add_padding_to_file(FILE *fptr, long long file_size) {  // Does NOT close the file.
    int check = file_size % AES_BLOCK_SIZE;
    
    if (check != 0) {
        fseek(fptr, 0, SEEK_END);

        int amount_to_add = AES_BLOCK_SIZE - check; // check for how many zeros have to be added for it to add up to a multiple of AES_BLOCK_SIZE
        unsigned char tmp_buffer[AES_BLOCK_SIZE];
        memset(tmp_buffer, 0, AES_BLOCK_SIZE);
        fwrite(tmp_buffer, sizeof(unsigned char), amount_to_add, fptr);   // pad the file

        fseek(fptr, 0, SEEK_SET);
    }
}

void encrypt_file(char *file_name, char *password) {
    FILE *fptr;

    AES_CTX ctx;
    unsigned char data_buffer[AES_BLOCK_SIZE];  //  bytes storing data; 16 bytes
    unsigned char *key = hash(password);

    long long file_size = get_file_size(file_name);
    fptr = fopen(file_name, "rb+");

    add_padding_to_file(fptr, file_size);
    AES_EncryptInit(&ctx, key);

    for (long long i = 0; i < file_size; i += AES_BLOCK_SIZE) {
        fread(data_buffer, sizeof(unsigned char), AES_BLOCK_SIZE, fptr);
        fseek(fptr, i, SEEK_SET);
        AES_Encrypt(&ctx, data_buffer, data_buffer);
        fwrite(data_buffer, sizeof(unsigned char), AES_BLOCK_SIZE, fptr);
    }
    
    AES_CTX_Free(&ctx);    
    fclose(fptr);

    char *new_name = (char *)calloc(255, sizeof(char));
    strcat(new_name, file_name);
    strcat(new_name, ".enc");
    rename(file_name, new_name);

    free(new_name);
    free(key);
}

void decrypt_file(char *file_name, char *password) {
    FILE *fptr;

    AES_CTX ctx;
    unsigned char data_buffer[AES_BLOCK_SIZE];  //  bytes storing data; 16 bytes
    unsigned char *key = hash(password);

    long long file_size = get_file_size(file_name);
    fptr = fopen(file_name, "rb+");

    AES_DecryptInit(&ctx, key);

    for (long long i = 0; i < file_size; i += AES_BLOCK_SIZE) {
        fread(data_buffer, sizeof(unsigned char), AES_BLOCK_SIZE, fptr);
        fseek(fptr, i, SEEK_SET);
        AES_Decrypt(&ctx, data_buffer, data_buffer);
        fwrite(data_buffer, sizeof(unsigned char), AES_BLOCK_SIZE, fptr);
    }
    
    AES_CTX_Free(&ctx);    
    fclose(fptr);

    char *new_name = (char *)calloc(255, sizeof(char));
    strcat(new_name, file_name);

    int index = strlen(new_name) - 1;
    for (int i = index; i > index - 4; i--) {
        new_name[i] = (char)0;
    }

    rename(file_name, new_name);

    free(new_name);
    free(key);
}