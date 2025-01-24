#include "algs.h"
#ifndef MAIN_ON






int test_flip_even(char test_case, char expected) {
	char buf[1] = { test_case };
	char output[1];
	buf[0] = (char)test_case;
	Flip_Even(buf, 1, output, 1);
	if (output[0] != expected) {
		printf("test_flip_even: Error! input %d, expected %d, got %d\n", test_case, expected, buf[0]);
		return 1;
	}
	else {
		return 0;
	}
}

int test_swap_3(char test_case, char expected) {
	char buf[1] = { test_case };
	char output[1];
	buf[0] = (char)test_case;
	Flip_Even(buf, 1, output, 1);
	if (output[0] != expected) {
		printf("test_flip_even: Error! input %d, expected %d, got %d\n", test_case, expected, buf[0]);
	}
	else {
		printf("test_flip_even: case %d passed\n", test_case);
	}
}

int test_rot5(char test_case, char expected) {
	char buf[1] = { test_case };
	char output[1];
	buf[0] = (char)test_case;
	Flip_Even(buf, 1, output, 1);
	if (output[0] != expected) {
		printf("test_flip_even: Error! input %d, expected %d, got %d\n", test_case, expected, buf[0]);
	}
	else {
		printf("test_flip_even: case %d passed\n", test_case);
	}
}

int test_main() {
	int tests_failed = 0;
	tests_failed += test_flip_even(0b11111111, 0b01010101);
	tests_failed += test_flip_even(0b10110011, 0b00011001);
	

	printf("%d tests failed\n", tests_failed);
}


#endif // !MAIN_ON