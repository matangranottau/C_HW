#include "algs.h"
#ifndef MAIN_ON




int test_None(char test_case, char expected) {
	char buf[1] = { test_case };
	char output[1];
	None(buf, 1, output, 1);
	if (output[0] != expected) {
		printf("test_none: Error! input %d, expected %d, got %d\n", test_case, expected, output[0]);
		return 1;
	}
	else {
		return 0;
	}
}

int test_flip_even(char test_case, char expected) {
	char buf[1] = { test_case };
	char output[1];
	Flip_Even(buf, 1, output, 1);
	if (output[0] != expected) {
		printf("test_flip_even: Error! input %d, expected %d, got %d\n", test_case, expected, buf[0]);
		return 1;
	}
	else {
		return 0;
	}
}

int test_swap_3(char byte1_in, char byte2_in, char byte1_expected, char byte2_expected) {
	char buf[2] = { byte1_in, byte2_in };
	char output[2];
	Swap_3(buf, 2, output, 2);
	if (output[0] != byte1_expected || output[1] != byte2_expected) {
		printf("test_swap_3: Error! input %d and %d, expected %d and %d, got %d and %d\n", byte1_in, byte2_in, byte1_expected, byte2_expected, output[0], output[1]);
		return 1;
	}
	else {
		return 0;
	}
}

int test_rot5(char test_case, char expected1, char expected2) {
	char buf[1] = { test_case };
	char output[2];
	Rotate_and_center_5(buf, 1, output, 2);
	if (output[0] != expected1 || output[1] != expected2) {
		printf("test_rot5: Error! input %d, expected %d and %d, got %d and %d\n", test_case, expected1, expected2, output[0], output[1]);
		return 1;
	}
	else {
		return 0;
	}
}

int test_main() {
	int tests_failed = 0;
	tests_failed += test_flip_even(0b11111111, 0b01010101);
	tests_failed += test_flip_even(0xB3, 0x19);
	tests_failed += test_flip_even(0b10110011, 0b00011001);
	tests_failed += test_swap_3(0b01011010, 0b01110001, 0b01011011, 0b01010001);
	tests_failed += test_swap_3(0b01010101, 0b01110001, 0b01010011, 0b10110001);
	tests_failed += test_rot5(0xAF, 0b00011110, 0b10100000);
	

	printf("%d tests failed\n", tests_failed);
}


#endif // !MAIN_ON