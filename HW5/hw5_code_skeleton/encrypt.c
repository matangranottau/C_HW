#include "encrypt.h"
#include "error_types.h"
#include "file_utils.h"
#include "algs.h"
#include <stdlib.h>

#define VALIDATE_EXIT(X) if (OK != X) return X;

int get_size_out(unsigned int in_buf_size, encrypt_t enc_type, int is_encrypt) {
    if (enc_type == ENC_TYPE_ROT_AND_CENTER_5) {
        if (is_encrypt) 
            return 2 * in_buf_size;
        return in_buf_size / 2;
    }
    return in_buf_size;
}

int encrypt_or_decrypt_buffer(unsigned char* in_buf, unsigned char* out_buf, int in_buf_size, int out_buf_size, encrypt_t enc_type, int is_encrypt) {
    switch (enc_type)
    {
    case ENC_TYPE_NONE:
        return None(in_buf, in_buf_size, out_buf, out_buf_size);
    case ENC_TYPE_FLIP_EVEN:
        return Flip_Even(in_buf, in_buf_size, out_buf, out_buf_size);
    case ENC_TYPE_SWAP_3:
        return Swap_3(in_buf, in_buf_size, out_buf, out_buf_size);
    case ENC_TYPE_ROT_AND_CENTER_5:
        if (is_encrypt)
            return Rotate_and_center_5(in_buf, in_buf_size, out_buf, out_buf_size);
        return Inv_Rotate_and_center_5(in_buf, in_buf_size, out_buf, out_buf_size);
    default:
        return ERR_BAD_FUNC_ARG;
    }

}

int encrypt_or_decrypt_file(const char* input_file_path, const char* output_file_path,
    encrypt_t enc_type, int is_encrypt) {
    int exit = 0;
    unsigned char* in_buf, *out_buf;
    unsigned int in_buf_size;
    unsigned int out_buf_size;

    if (input_file_path == NULL || output_file_path == NULL) {
        return ERR_NULL_PTR;
    }


    // load from file data to buffer
    exit = load_data_from_file(input_file_path, &in_buf, &in_buf_size);
    if (OK != exit) {
        free(in_buf);
        return exit;
    }

    out_buf_size = get_size_out(in_buf_size, enc_type, is_encrypt);
    exit = allocate_buffer(&out_buf, out_buf_size);
    if (OK != exit) {
        free(in_buf);
        return exit;
    }

    // encrypt by enc_type
    exit = encrypt_or_decrypt_buffer(in_buf, out_buf, in_buf_size, out_buf_size, enc_type, is_encrypt);

    // free in_buf, write to output file.
    free(in_buf);
    if (OK != exit) {
        free(out_buf);
        return exit;
    }

    exit = write_data_to_file(output_file_path, out_buf, out_buf_size);
    free(out_buf);

    return exit;
}

int encrypt_file(const char *input_file_path, const char *output_file_path,
                 encrypt_t enc_type) {
    return encrypt_or_decrypt_file(input_file_path, output_file_path, enc_type, 1);
}

int decrypt_file(const char *input_file_path, const char *output_file_path,
                 encrypt_t enc_type) {
    return encrypt_or_decrypt_file(input_file_path, output_file_path, enc_type, 0);
}
