#define _CRT_SECURE_NO_WARNINGS
#include "algs.h"
#include "censor.h"
#include "parser.h"
#include "error_types.h"
#include <string.h>
#include <stdlib.h>
#ifndef MAIN_ON

/* Parser Tests: */
int test_parse_args(int argc, char** argv, command_t* p_cmd_expected, int exit_expected) {
	command_t cmd;
	command_t* p_cmd = &cmd;
	int exit = parse_args(argc, argv, p_cmd);
	if (exit != exit_expected) {
		printf("test_parse_args: Error! in %s expected %d, got %d\n", argv[0], exit_expected, exit);
		return 1;
	}
	int k = strcmp(p_cmd->input_path, p_cmd_expected->input_path) + strcmp(p_cmd->output_path, p_cmd_expected->output_path);
	if (strcmp("ignore", p_cmd_expected->blacklist_path)) {
		k += strcmp(p_cmd->blacklist_path, p_cmd_expected->blacklist_path);
	}

	if (p_cmd->op != p_cmd_expected->op || p_cmd->enc_type != p_cmd_expected->enc_type || k != 0) {
		printf("test_parse_args: Error! in %s parser passed wrong arguments", argv[0]);
		return 1;
	}
	return 0;
}


/* ENC/DEC/CESNOR Tests: */
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
int test_censor_string(char* str, char* cen_word, char* expected_str) {
	char* cen_str = (char*)malloc(strlen(str));
	strcpy(cen_str, str);
	censor_string(&cen_str, cen_word, strlen(str), strlen(cen_word));
	if (0 != strcmp(cen_str, expected_str)) {
		printf("test_censor_string: Error! censored word is: %s, expected: %s, got: %s \n", cen_word, expected_str, cen_str);
		free(cen_str);
		return 1;
	}

	return 0;
}

int test_main() {
	int tests_failed = 0;
	
	
	/* Parser Tests: */
	command_t p_cmd_expected1 = { OP_ENC, ENC_TYPE_NONE, "in_txt", "out_txt", "ignore" };
	char* argv1[] = { "test1", "-p", "enc", "-t", "0", "-i", "in_txt", "-o", "out_txt" };
	test_parse_args(9, argv1, &p_cmd_expected1, OK);
	
	
	/* ENC/DEC/CESNOR Tests: */
	tests_failed += test_flip_even(0b11111111, 0b01010101);
	tests_failed += test_flip_even(0xB3, 0x19);
	tests_failed += test_flip_even(0b10110011, 0b00011001);
	tests_failed += test_swap_3(0b01011010, 0b01110001, 0b01011011, 0b01010001);
	tests_failed += test_swap_3(0b01010101, 0b01110001, 0b01010011, 0b10110001);
	tests_failed += test_rot5(0xAF, 0b00011110, 0b10100000);
	tests_failed += test_censor_string(" he llo IM blue daboo dee blueb dbaa BLue Daboode", "blue", " he llo IM **** daboo dee blueb dbaa **** Daboode");
	tests_failed += test_censor_string(" he llo IM !blUe? daboo/ dee bl!ueb dbaa BLue ?Daboode", "blue", " he llo IM !****? daboo/ dee bl!ueb dbaa **** ?Daboode");
	tests_failed += test_censor_string(" ", "blue", " ");
	tests_failed += test_censor_string("", "blue", "");
	tests_failed += test_censor_string("bro wh8t the fuck", "fuck", "bro wh8t the ****");
	tests_failed += test_censor_string("bro wh8t the fuck", "", "bro wh8t the fuck");

	printf("%d tests failed\n", tests_failed);
}


#endif // !MAIN_ON