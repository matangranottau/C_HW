#include "algs.h"
#include "error_types.h"
#include <stdio.h>

// TODO: Add the function implementations in here.

// None:
int None(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out){
	if (data_in == NULL || data_out == NULL) {
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
int Flip_Even(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out) {
	if (data_in == NULL || data_out == NULL) {
		return ERR_NULL_PTR;
	}
	if (size_in > size_out) {
		return ERR_BAD_FUNC_ARG;
	}
	for (unsigned int i = 0; i < size_in; i++) {
		if (i % 2 == 0) {
			data_out[i] = ~data_in[i]; // ~ is bitwise not 
		}
		else {
			data_out[i] = data_in[i];
		}
	}
	return OK;
}

// Swap 3:
int Swap_3(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out){
	if (data_in == NULL || data_out == NULL) {
		return ERR_NULL_PTR;
	}
	if (size_in > size_out) {
		return ERR_BAD_FUNC_ARG;
	}
	for (unsigned int i = 0; i < size_in; i+= 2) {
		char LSB_3 = data_in[i] & 0b00000111; // bit manipulatin to get the lsb
		char MSB_3 = (data_in[i + 1] & 0b11100000) >> 5; // bit manipulatin to get the msb
		data_out[i] = (data_in[i] & 0b11111000) | MSB_3; // or with 0 iz the original byte
		data_out[i + 1] = (data_in[i + 1] & 0b00011111) | (LSB_3 << 5);

	if (size_in % 2 != 0) {
		data_out[size_in - 1] = data_in[size_in - 1]; //if not even last bit stay the same
	}
	return OK;
	}
}

// Rot and Center 5:
int Rotate_and_center_5(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out){
	if (data_in == NULL || data_out == NULL) {
		return ERR_NULL_PTR;
	}
	if (size_in > size_out) {
		return ERR_BAD_FUNC_ARG;
	}
	for (unsigned int i = 0; i < size_in; i++) {
		unsigned char rotated = (data_in[i] >> 5) | (data_in[i] << 3); // rotating by shifting the bytes
		data_out[i] = rotated ^ 0b10101010; 
	}

	return OK;
}

int Inv_Rotate_and_center_5(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out){}


