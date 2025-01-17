#define _CRT_SECURE_NO_WARNINGS
#include "file_utils.h"
#include "error_types.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_WORD_SIZE 256

int get_file_size(const char* input_file_path) {
    int size = 0;
    FILE* fPtrRead = NULL;
    
    fPtrRead = fopen(input_file_path, "r");
    if (fPtrRead == NULL) {
        return ERR_FILE;
    }

    while (!feof(fPtrRead)) {
        fseek(fPtrRead, sizeof(char), 1); // advance by one char
        size++;
    }
    fclose(fPtrRead);

    return size;
}
int allocate_buffer(void **buf, unsigned int buf_size) {
    
  return OK;
}

int write_data_to_file(const char *output_file_path, const unsigned char *buf,
                       unsigned int buf_size) {
    
    return OK;
}

int load_data_from_file(const char *input_file_path, unsigned char **buf,
                        unsigned int *buf_size) {
   
    return OK;
}

// Function to load blacklisted words from a file
int load_array_of_words(const char *input_file_path, char ***array,
                        unsigned int *p_cnt) {
  // TODO
  return OK;
}
