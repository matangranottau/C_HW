#include "file_utils.h"
#include "error_types.h"
#include <stdio.h>

#define MAX_WORD_SIZE 256

int allocate_buffer(void **buf, unsigned int buf_size) {
  // TODO
    if (buf == NULL ){
        return ERR_NULL_PTR;
    }
    if (buf_size == 0) {
        return ERR_BAD_FUNC_ARG;
    }
    *buf = malloc(buf_size);
    if (*buf = NULL) {
        return ERR_MEMORY;
    }
  return OK;
}

int write_data_to_file(const char *output_file_path, const unsigned char *buf,
                       unsigned int buf_size) {
  // TODO
    if (output_file_path == NULL || buf == NULL) {
        return ERR_NULL_PTR;
    }
    if (buf_size == 0) {
        return ERR_BAD_ENC_TYPE;
    }
    FILE* file = fopen(output_file_path, "wb"); // open file
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

int load_data_from_file(const char *input_file_path, unsigned char **buf,
                        unsigned int *buf_size) {
  // TODO
  return OK;
}

// Function to load blacklisted words from a file
int load_array_of_words(const char *input_file_path, char ***array,
                        unsigned int *p_cnt) {
  // TODO
  return OK;
}
