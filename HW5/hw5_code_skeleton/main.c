#include "error_types.h"
#include "parser.h"
// TODO - add you includes here
#include "encrypt.h"
#include "censor.h"
#include <stdio.h>
#include <stdlib.h>
#include "algs.h"
#define MAIN_ON 1
#define TEST_ADD_SUFFIX 0
#define TEST_CENSOR 0

void print_status(int exit_code) {
	switch (exit_code)
	{
	case OK:
		printf("Program exited successfully.\n");
		break;
	case ERR_NUM_ARGS:
		printf("Program failed. Error: ERR_NUM_ARGS\n");
		break;
	case ERR_MISSING_ARG:
		printf("Program failed. Error: ERR_MISSING_ARG\n");
		break;
	case ERR_UNKNOWN_FLAG:
		printf("Program failed. Error: ERR_UNKNOWN_FLAG\n");
		break;
	case ERR_BAD_OP:
		printf("Program failed. Error: ERR_BAD_OP\n");
		break;
	case ERR_BAD_ENC_TYPE:
		printf("Program failed. Error: ERR_BAD_ENC_TYPE\n");
		break;
	case ERR_NULL_PTR:
		printf("Program failed. Error: ERR_NULL_PTR\n");
		break;
	case ERR_MEMORY:
		printf("Program failed. Error: ERR_MEMORY\n");
		break;
	case ERR_FILE:
		printf("Program failed. Error: ERR_FILE\n");
		break;
	case ERR_BAD_FUNC_ARG:
		printf("Program failed. Error: ERR_BAD_FUNC_ARG\n");
		break;
	default:
		break;
	}
}
static int process_operation(command_t cmd) {
	int exit = 0;
	if (cmd.input_path == NULL || cmd.output_path == NULL) {
		return ERR_NULL_PTR;
	}
	switch (cmd.op)
	{
	case OP_ENC:
		exit = encrypt_file(cmd.input_path, cmd.output_path, cmd.enc_type);
		break;
	case OP_DEC:
		exit = decrypt_file(cmd.input_path, cmd.output_path, cmd.enc_type);
		break;
	case OP_CENSOR:
		exit = censor_and_encrypt(cmd.input_path, cmd.output_path, cmd.enc_type, cmd.blacklist_path);
		break;
	default:
		return ERR_BAD_ENC_TYPE;
	}

  return exit;
}

#if MAIN_ON
int main(int argc, const char* argv[]) {
	int exit = 0;
	if (argc <= 1) {
		print_help();
		return OK;
	}
	command_t cmd;
	cmd.input_path = "";
	cmd.output_path = "";
	cmd.blacklist_path = "";
	exit = parse_args(argc, argv, &cmd);
	if (exit != OK) {
		print_status(exit);
		return exit;
	}
	exit = process_operation(cmd);
	print_status(exit);
	

	return exit;
}
#else
int main(char* argv[], int argc) {
	test_main();
	return 0;
}

#endif // MAIN_ON



