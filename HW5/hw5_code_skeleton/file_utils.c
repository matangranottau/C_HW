#define _CRT_SECURE_NO_WARNINGS
#include "file_utils.h"
#include "error_types.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_WORD_SIZE 256


int allocate_buffer(void **buf, unsigned int buf_size) {
 
    if (buf == NULL){
        return ERR_NULL_PTR;
    }
    if (buf_size == 0) {
        return ERR_BAD_FUNC_ARG;
    }
    *buf = malloc(buf_size);
    if (*buf == NULL) {
        return ERR_MEMORY;
    }
    return OK;
}

int write_data_to_file(const char* output_file_path, const unsigned char* buf,
    unsigned int buf_size) {
   
    if (output_file_path == NULL || buf == NULL) {
        return ERR_NULL_PTR;
    }
    if (buf_size == 0) {
        return ERR_BAD_ENC_TYPE;
    }
    FILE* file = fopen(output_file_path, "w"); // open file
    if (file == NULL) {
        return ERR_FILE;
    }
    size_t written = fwrite(buf, 1, buf_size, file); // write to the file
    fclose(file); // close the fike
    if (written != buf_size) {
        return ERR_FILE;
    }
    return OK;
}

int load_data_from_file(const char* input_file_path, unsigned char** buf,
    unsigned int* buf_size) {

    if (input_file_path == NULL || buf == NULL || buf_size == NULL) {
        return ERR_NULL_PTR;
    }
    FILE* file = fopen(input_file_path, "r"); // open file
    if (file == NULL) {
        return ERR_FILE;
    }

    fflush(file);
    fseek(file, 0, SEEK_END);
    long size = ftell(file); //checking the size of the file
    rewind(file);
    

    if (size < 0) {
        fclose(file);
        return ERR_FILE;
    }
    int res = allocate_buffer(buf, size);
    if (res != OK) {
        return res;
    }
    if (*buf == NULL) {
        printf("*buf is null!\n");
        return 1;
    }
    
    size_t read = fread(*buf, 1, size, file); // reading
    fclose(file);

    if (read > size) { // error in reading the file
        free(*buf);
        return ERR_FILE;
    }
    *buf_size = (unsigned int)size;
    return OK;
}

// Function to load blacklisted words from a file
int load_array_of_words(const char* input_file_path, char*** array,
    unsigned int* p_cnt) {
   
    if (input_file_path == NULL || array == NULL || p_cnt == NULL) {
        return ERR_NULL_PTR;
    }
    FILE* file = fopen(input_file_path, "r");
    if (file == NULL) {
        return ERR_FILE;
    }
    char** words = NULL;
    char word[MAX_WORD_SIZE];
    unsigned int cnt = 0;

    while (fgets(word, MAX_WORD_SIZE, file) != NULL) {
        // Remove newline character, if present
        size_t len = strlen(word);
        if (len > 0 && word[len - 1] == '\n') {
            word[len - 1] = '\0';
        }
        char** temp = realloc(words, (cnt + 1) * sizeof(char*));
        if (temp == NULL) {
            fclose(file);
            for (int i = 0; i < cnt; i++) {
                free(words[i]);
            }
            free(words);
            return ERR_MEMORY;
        }
        words = temp;

        words[cnt] = malloc(strlen(word) + 1);
        if (words[cnt] == NULL) {
            fclose(file);
            for (int i = 0; i < cnt; i++) {
                free(words[i]);
            }
            free(words);
            return ERR_MEMORY;
        }
        strcpy(words[cnt], word);
        cnt++;
    }

    fclose(file);
    *array = words;
    *p_cnt = cnt;

    return OK;
}