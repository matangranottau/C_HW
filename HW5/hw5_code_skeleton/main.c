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
#endif // MAIN_ON


#if TEST_CENSOR
int main(int argc, const char* argv[]) {
	char* buff_1 = "Hello, im matan";
	char* cen_1[2] = { "Hello", "im" };
	//censor(&buff_1, cen_1, 15, 2);
	//printf("%s\n", buff_1);

	char buff_2[12] = {'h', 'e', 'l', 'l', 'o', 'i', 'm', 'm', 'a', 't', 'a', 'n'};
	char* cen_2[2] = { "Hello", "im" };
	//censor(&buff_2, cen_2, 12, 2);
	//printf("%s\n", buff_2);
	

	char* hds_str = "can you save?\n, can you save my..?\n can you save my .. HEAVYDIRTYSOUL??";
	printf("strlen of str1 + 1 is %d\n", strlen(hds_str) + 1);
	char* str_2 = (char*)malloc(strlen(hds_str) + 1);
	if (str_2 == NULL) {
		printf("error\n");
		return 1;
	}
	strcpy(str_2, hds_str);
	censor_string(&str_2, "save", strlen(str_2), strlen("save"));
	printf("%s\n", str_2);
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
