#include "error_types.h"
#include "parser.h"
// TODO - add you includes here
#include <stdio.h>

static int process_operation(command_t cmd) {
  // TODO:
  // Assuming cmd is OK, no need to validate members as they are beeing
  // validated inside parse args & within each processed operation.

  // TODO: process command according to operation

  return OK;
}

int main(int argc, const char *argv[]) {

  // TODO: check if need to print help (no args or 1 arg and its help) and print it.
	if (argc <= 1) {
		print_help();
  }
  // TODO: call parse arguments of parser
	else {
		command_t cmd;
		cmd.input_path = "";
		cmd.output_path = "";
		cmd.blacklist_path = "";
		parse_args(argc, argv, &cmd);

	}
  // TODO: run command - call process operation

  return 0;
}
