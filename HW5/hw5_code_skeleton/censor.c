#include "censor.h"
#include "error_types.h"
#include "encrypt.h"
#include "file_utils.h"
#include <stdlib.h>

void add_suffix(const char* output_censored_path, char** ptr_output_encrypted_path) {
    // TODO: replaces ".txt" suffix to "_enc.txt"
}

void censor(char** buff, const char** blacklist_array, const int buf_size) {
    // TODO: input buffer gets censored with blacklist.
}

void censor_file(const char* input_path, const char* blacklist_path, const char* output_censored_path) {
    char** blacklist_array;
    char* buf;
    unsigned int cnt, buf_size = get_file_size(input_path);

    load_array_of_words(blacklist_path, &blacklist_array, &cnt);

    load_data_from_file(input_path, &buf, &buf_size);

    censor(&buf, blacklist_array, buf_size);

    write_data_to_file(output_censored_path, buf, buf_size);

}

int censor_and_encrypt(const char *input_path, const char *output_censored_path,
                       encrypt_t enc_type, const char *blacklist_path) {
    char* output_encrypted_path;
    add_suffix(output_censored_path, &output_encrypted_path);
    
    encrypt_file(input_path, output_encrypted_path, enc_type);
    
    censor_file(input_path, blacklist_path, output_censored_path);

    if (input_path == NULL || output_censored_path == NULL || blacklist_path == NULL) {
        return ERR_NULL_PTR;
    }
    if (enc_type == ENC_TYPE_LAST) {
        return ERR_BAD_FUNC_ARG;
    }

  return OK;
}
