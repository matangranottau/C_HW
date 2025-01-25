#define _CRT_SECURE_NO_WARNINGS
#include "censor.h"
#include "error_types.h"
#include "encrypt.h"
#include "file_utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define VALIDATE(X) if(OK != X) return X;


int is_eq(const char* str1, const char* str2, const int n) {
    for (int i = 0; i < n; i++) {
        if (tolower(str1[i]) != tolower(str2[i])) {
            return 0;
        }
    }
    return 1;
}
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

int add_suffix(const char* output_censored_path, char** ptr_output_encrypted_path) {
    int exit = OK;
    char* new_suffix = "_enc.txt";
    int old_suffix_len = 4, new_suffix_len = 8;
    int old_len = strlen(output_censored_path), new_len = old_len + (new_suffix_len - old_suffix_len);

    exit = allocate_buffer(ptr_output_encrypted_path, new_len + 1); // + 1 for null terminator
    VALIDATE(exit);

    strncpy(*ptr_output_encrypted_path, output_censored_path, old_len - old_suffix_len); // copy all char until .txt from censored
    *ptr_output_encrypted_path[old_len - old_suffix_len] = '\0'; // strncpy doesn't null terminates for some reason
    strcat(*ptr_output_encrypted_path, new_suffix);
    
    return OK;
}

void censor_string(char** p_str, const char* cen_word, const int str_len, const int cen_word_len) {
    if (str_len <= cen_word_len) // if blacklist word longer than str, no censor will occur
        return; 

    for (int j = 0; j < str_len - cen_word_len; j++) {

        if (j == 0 && is_special(*p_str, j + cen_word_len + 1)) {
            if (is_eq(*p_str, cen_word, cen_word_len)) {
                put_astrik(*p_str, 0, j + cen_word_len - 1);
                j += cen_word_len - 1;
            }
        }
        else if (is_special(*p_str, j) && is_special(*p_str, j + cen_word_len + 1)) {

            if (is_eq(*p_str + j + 1, cen_word, cen_word_len)) {
                put_astrik(*p_str, j + 1, j + cen_word_len);
                j += cen_word_len;
            }
        }

    }
}

int censor(char** buff, const char** blacklist_array, const int buf_size, const int blacklist_size) {
    int exit = OK;
    char* str = NULL;
    exit = allocate_buffer(&str, buf_size + 1);
    VALIDATE(exit);

    memcpy(str, *buff, buf_size);
    str[buf_size] = '\0';

    for (int i = 0; i < blacklist_size; i++) {
        censor_string(&str, blacklist_array[i], strlen(str), strlen(blacklist_array[i]));
    }

    free(*buff);
    *buff = str;

    return OK;
}


int censor_file(const char* input_path, const char* blacklist_path, const char* output_censored_path) {
    int exit = OK;
    char** blacklist_array;
    char* buf;
    unsigned int cnt, buf_size;

    exit = load_data_from_file(input_path, &buf, &buf_size);
    VALIDATE(exit);

    exit = load_array_of_words(blacklist_path, &blacklist_array, &cnt);
    if (OK != exit) {
        free(buf);
        return exit;
    }

    exit = censor(&buf, blacklist_array, buf_size, cnt);
    
    for (int i = 0; i < cnt; i++) {
        free(blacklist_array[i]);
    }
    free(blacklist_array);

    if (OK != exit) {
        free(buf);    
        return exit;
    }

    exit = write_data_to_file(output_censored_path, buf, buf_size);
    free(buf);
    return exit;
}

int censor_and_encrypt(const char *input_path, const char *output_censored_path,
                       encrypt_t enc_type, const char *blacklist_path) {
    char* output_encrypted_path;
    if (NULL == blacklist_path || NULL == input_path || NULL == output_censored_path) {
        return ERR_NULL_PTR;
    }
    int exit = 0;
    exit = add_suffix(output_censored_path, &output_encrypted_path);
    VALIDATE(exit);
    
    exit = encrypt_file(input_path, output_encrypted_path, enc_type);
    free(output_encrypted_path);
    VALIDATE(exit);
    
    exit = censor_file(input_path, blacklist_path, output_censored_path);
    VALIDATE(exit);


  return OK;
}
