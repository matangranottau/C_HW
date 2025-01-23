#define _CRT_SECURE_NO_WARNINGS
#include "censor.h"
#include "error_types.h"
#include "encrypt.h"
#include "file_utils.h"
#include <stdlib.h>
#include <string.h>

void put_astrik(char* str, const int idx1 , const int idx2) {
    for (int i = idx1; i <= idx2; i++) {
        str[i] = '*';
    }
}

int is_special(const char* str, const int idx) {
    const char* special_chars = "\\\n\r\t ‘!()[]{}<>,.:;\"-_=+/?";
    
    if (str[idx] == '\0') { // in case we reach end of str
        return 1;
    }
    
    for (int i = 0; special_chars[i] != '\0'; i++) {
        if (special_chars[i] == str[idx]) {
            return 1;
        }
    }
    
    return 0;
}

void add_suffix(const char* output_censored_path, char** ptr_output_encrypted_path) {
    char* new_suffix = "_enc.txt";
    int old_suffix_len = 4, new_suffix_len = 8;
    int old_len = strlen(output_censored_path), new_len = old_len + (new_suffix_len - old_suffix_len);

    char* str = (char*)malloc(new_len + 1); // + 1 for null terminator
    
    strncpy(str, output_censored_path, old_len - old_suffix_len); // copy all char until .txt from censored
    str[old_len - old_suffix_len] = '\0'; // strncpy doesn't null terminates for some reason
    strcat(str, new_suffix);
    *ptr_output_encrypted_path = str;
    
}

void censor(char** buff, const char** blacklist_array, const int buf_size, const int blacklist_size) {

    char* str = (char*)malloc(buf_size + 1);
    memcpy(str, *buff, buf_size);
    str[buf_size] = '\0';
    int str_len = strlen(str);

    for (int i = 0; i < blacklist_size; i++) {
        
        int n = strlen(blacklist_array[i]);
        
        if (str_len > n) { // if blacklist word longer than str, no censor will occur
            for (int j = 0; j < str_len - n; j++) {

                if (j == 0 && is_special(str, j + n + 1)) {
                    if (strncmp(str, blacklist_array[i], n) == 0) {
                        put_astrik(str, 0, j + n - 1); 
                        j += n - 1;
                    }
                }
                else if (is_special(str, j) && is_special(str, j + n + 1)) {

                    if (strncmp(str + j + 1, blacklist_array[i], n) == 0) {
                        put_astrik(str, j + 1, j + n);
                        j += n;
                    }
                }

            }
        }
    }

    char* uncensored_buff = *buff;
    *buff = str;
    //free(uncensored_buff);
        
}


void censor_file(const char* input_path, const char* blacklist_path, const char* output_censored_path) {
    char** blacklist_array;
    char* buf;
    unsigned int cnt, buf_size = get_file_size(input_path);

    load_array_of_words(blacklist_path, &blacklist_array, &cnt);

    load_data_from_file(input_path, &buf, &buf_size);

    censor(&buf, blacklist_array, buf_size, cnt);

    write_data_to_file(output_censored_path, buf, buf_size);

    
}

int censor_and_encrypt(const char *input_path, const char *output_censored_path,
                       encrypt_t enc_type, const char *blacklist_path) {
    char* output_encrypted_path;
    add_suffix(output_censored_path, &output_encrypted_path);
    
    encrypt_file(input_path, output_encrypted_path, enc_type);
    
    free(output_encrypted_path);
    
    censor_file(input_path, blacklist_path, output_censored_path);

    if (input_path == NULL || output_censored_path == NULL || blacklist_path == NULL) {
        return ERR_NULL_PTR;
    }
    if (enc_type == ENC_TYPE_LAST) {
        return ERR_BAD_FUNC_ARG;
    }

  return OK;
}
