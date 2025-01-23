#include "error_types.h"
#include "parser.h"
// TODO - add you includes here
#include "encrypt.h"
#include "censor.h"
#include <stdio.h>
#include "algs.h"
#define MAIN_ON 0
#define TEST_ADD_SUFFIX 0
#define TEST_CENSOR 1


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
#endif // MAIN_ON


#if TEST_CENSOR
int main(int argc, const char* argv[]) {
	char* buff_1 = "Hello, im matan";
	char* cen_1[2] = { "Hello", "im" };
	censor(&buff_1, cen_1, 15, 2);
	printf("%s\n", buff_1);

	char buff_2[12] = {'h', 'e', 'l', 'l', 'o', 'i', 'm', 'm', 'a', 't', 'a', 'n'};
	char* cen_2[2] = { "Hello", "im" };
	censor(&buff_2, cen_2, 12, 2);
	printf("%s\n", buff_2);
	return 0;
}
#endif // TEST_CENSOR


#if TEST_ADD_SUFFIX
int main(int argc, const char* argv[]) {
	char* out;
	char* in_1 = "text.txt";
	char* in_2 = "blahblahblahh\out.txt";
	add_suffix(in_1, &out);
	printf("%s\n", out);

	add_suffix(in_2, &out);
	printf("%s\n", out);

	return 0;
}
#endif // TEST_ADD_SUFFIX
