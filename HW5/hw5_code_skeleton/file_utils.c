#include "file_utils.h"
#include "error_types.h"
#include <stdlib.h>

#define MAX_WORD_SIZE 256

int allocate_buffer(void **buf, unsigned int buf_size) {
    if (buf == NULL) {
        return ERR_NULL_PTR;
    }
    
    *buf = (char*)malloc(MAX_WORD_SIZE * sizeof(char)); // Memory allocation for buffer

    if (*buf == NULL) {
        return ERR_MEMORY;
    }
  return OK;
}

int write_data_to_file(const char *output_file_path, const unsigned char *buf,
                       unsigned int buf_size) {
  // TODO
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
