#include "encrypt.h"
#include "error_types.h"
#include "file_utils.h"
#include "algs.h"
#include <stdlib.h>

int get_size_out(unsigned int in_buf_size, encrypt_t enc_type) {
    if (enc_type == ENC_TYPE_NONE || enc_type == ENC_TYPE_FLIP_EVEN || enc_type == ENC_TYPE_SWAP_3) {
        return in_buf_size;
    }
    else if (enc_type == ENC_TYPE_ROT_AND_CENTER_5) {
        return 2 * in_buf_size;
    }
}
int encrypt_file(const char *input_file_path, const char *output_file_path,
                 encrypt_t enc_type) {
    unsigned char* in_buf, *out_buf;
    unsigned int in_buf_size = get_file_size(input_file_path);
    unsigned int out_buf_size = get_size_out(in_buf_size, enc_type);
    
    // TODO: errors
    if (input_file_path == NULL || output_file_path == NULL) {
        return ERR_NULL_PTR;
    }

    if (enc_type == ENC_TYPE_LAST) {
        return ERR_BAD_FUNC_ARG;
    }


    // load from file data to buffer, create new buffer
    load_data_from_file(input_file_path, &in_buf, &in_buf_size);
    allocate_buffer(&out_buf, out_buf_size);
    
    // encrypt by enc_type
    switch (enc_type)
    {
    case ENC_TYPE_NONE:
        None(in_buf, in_buf_size, out_buf, out_buf_size);
        break;
    case ENC_TYPE_FLIP_EVEN:
        Flip_Even(in_buf, in_buf_size, out_buf, out_buf_size);
        break;
    case ENC_TYPE_SWAP_3:
        Swap_3(in_buf, in_buf_size, out_buf, out_buf_size);
        break;
    case ENC_TYPE_ROT_AND_CENTER_5:
        Rotate_and_center_5(in_buf, in_buf_size, out_buf, out_buf_size);
        break;
    default:
        return ERR_BAD_FUNC_ARG;
        break;
    }
  
    // free in_buf, write to output file.
    free(in_buf);
    write_data_to_file(output_file_path, out_buf, out_buf_size);
    return OK;
}

int decrypt_file(const char *input_file_path, const char *output_file_path,
                 encrypt_t enc_type) {
    
    if (enc_type != ENC_TYPE_ROT_AND_CENTER_5) { // inversable encryption case.
        return encrypt_file(input_file_path, output_file_path, enc_type);
  }
    else if (enc_type == ENC_TYPE_ROT_AND_CENTER_5) {
        unsigned char* in_buf, * out_buf;
        unsigned int in_buf_size = get_file_size(*input_file_path);
        unsigned int out_buf_size = in_buf_size / 2 ;
        if (input_file_path == NULL || output_file_path == NULL) {
            return ERR_NULL_PTR;
        }

        if (enc_type == ENC_TYPE_LAST) {
            return ERR_BAD_FUNC_ARG;
        }

        // load from file data to buffer, create new buffer.
        load_data_from_file(input_file_path, &in_buf, &in_buf_size);
        allocate_buffer(&out_buf, out_buf_size);

        // decrypt.
        Inv_Rotate_and_center_5(in_buf, in_buf_size, out_buf, out_buf_size);

        // free in_buf, write to output file.
        free(in_buf);
        write_data_to_file(output_file_path, out_buf, out_buf_size);
        return OK;
    }
  return OK;
}
