#include "error_types.h"
#include "parser.h"
// TODO - add you includes here
#include "encrypt.h"
#include "censor.h"
#include <stdio.h>
#include "algs.h"

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

/*int main(int argc, const char* argv[]) {
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
*/
int main(int argc, const char* argv[]) {
	char* str_in = "hello";
	char* str_out;
	None(str_in, 6, str_out, 6);
	printf("%s", str_out);

	return 0;
}