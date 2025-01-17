#ifndef __algs_H__
#define __algs_H__

typedef enum {
  ENC_TYPE_NONE = 0,

  ENC_TYPE_FLIP_EVEN,
  ENC_TYPE_SWAP_3,
  ENC_TYPE_ROT_AND_CENTER_5,

  ENC_TYPE_LAST
} encrypt_t;

// the different encryption functions

int None(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out);

int Flip_Even(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out);

int Swap_3(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out);

int Rotate_and_center_5(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out);

int Inv_Rotate_and_center_5(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out);
#endif //__algs_H__
