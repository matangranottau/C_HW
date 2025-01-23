#include "error_types.h"
#include "parser.h"
// TODO - add you includes here
#include "encrypt.h"
#include "censor.h"
#include <stdio.h>
#include "algs.h"
#define ADD_SUFFIX_TEST 0


#if ADD_SUFFIX_TEST
#include "censor.h"
#endif // ADD_SUFFIX_TEST


static int process_operation(command_t cmd) {
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

#if ADD_SUFFIX_TEST
main(int argc, const char* argv[]) {
	char* out;
	char* in_1 = "text.txt";
	char* in_2 = "blahblahblahh\out.txt";
	add_suffix(in_1, &out);
	printf("%s\n", out);

	add_suffix(in_2, &out);
	printf("%s\n", out);

	return 0;
}
#endif // ADD_SUFFIX_TEST
