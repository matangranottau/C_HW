#ifndef __CENSOR_H__
#define __CENSOR_H__

#include "algs.h" // for encrypt_t

void censor_string(char** p_str, const char* cen_word, const int str_len, const int cen_word_len);

int add_suffix(const char* output_censored_path, char** ptr_output_encrypted_path);

// censor and encrypt main function
int censor_and_encrypt(const char *input_path, const char *output_censored_path,
                       encrypt_t enc_type, const char *blacklist_path);

#endif //__CENSOR_H__
