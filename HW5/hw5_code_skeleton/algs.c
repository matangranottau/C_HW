#include "algs.h"
#include "error_types.h"

// TODO: Add the function implementations in here.

// None:
int None(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out){
	if (data_in == 0 || data_out == 0) {
		return ERR_NULL_PTR;
	}
	if (size_in > size_out) {
		return ERR_BAD_FUNC_ARG;
	}
	for (unsigned int i = 0; i < size_in; i++) { //basicly doing nothing
		data_out[i] = data_in[i];
	}
	return OK;
}

// Flip Even:


// Swap 3:

// Rot and Center 5:



int None(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out){}

int Flip_Even(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out) {}

int Swap_3(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out) {}

int Rotate_and_center_5(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out) {}

int Inv_Rotate_and_center_5(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out) {}