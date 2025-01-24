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


static int process_operation(command_t cmd) {
	if (cmd.input_path == NULL) {
		return 1;
	}
	if (cmd.output_path == NULL) {
		return 1;
	}
	switch (cmd.op)
	{
	case OP_ENC:
		encrypt_file(cmd.input_path, cmd.output_path, cmd.enc_type);
		break;
	case OP_DEC:
		decrypt_file(cmd.input_path, cmd.output_path, cmd.enc_type);
		break;
	case OP_CENSOR:
		censor_and_encrypt(cmd.input_path, cmd.output_path, cmd.enc_type, cmd.blacklist_path);
		break;
	default:
		return ERR_BAD_FUNC_ARG;
	}

  return OK;
}

#if MAIN_ON
int main(int argc, const char* argv[]) {
	if (argc <= 1) {
		print_help();
	}
	else {
		command_t cmd;
		cmd.input_path = "";
		cmd.output_path = "";
		cmd.blacklist_path = "";
		parse_args(argc, argv, &cmd);
		process_operation(cmd);
	}

	return 0;
}
#else
int main(char* argv[], int argc) {
	test_main();
	return 0;
}

#endif // MAIN_ON



