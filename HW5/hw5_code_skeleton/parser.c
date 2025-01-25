#define _CRT_SECURE_NO_WARNINGS
#include "parser.h"
#include "error_types.h"
#include <stdio.h>
#include <string.h>
#define FLAGS_LEN(flags) (sizeof(flags) / sizeof(flag_t))
#define ENCRYPT_ARG_NUM 4
#define CENSOR_ARG_NUM 5

typedef struct {
  const char *short_name;
  const char *long_name;
  const char *description;
} flag_t;

static const flag_t flags[] = {{HELP_FLAG, "help", "print this description"},
                               {"-p", "operation", "enc/dec/censor"},
                               {"-t", "encryption type", "0/1/2/3"},
                               {"-i", "input", "file path"},
                               {"-o", "output", "file path"},
                               {"-b", "blacklist", "file path"}};

int isFlag(char* str) {
    if (str[0] == '-') {
        return 1;
    }
    return 0;
}
void print_help() {
  printf("Usage:\n");
  for (int i = 0; i < FLAGS_LEN(flags); i++) {
    printf("%*s%*s: %s,\n", 4, flags[i].short_name, 17, flags[i].long_name,
           flags[i].description);
  }
  printf("Please try again.\n");
}

int parse_args(int argc, const char *argv[], command_t *p_cmd) {
    int p_raise = 0, t_raise = 0, i_raise = 0, o_raise = 0, b_raise = 0;
    for (int j = 1; j < argc; j++) {
        if (strcmp(argv[j], "-h") == 0) {  // "-h" help flag (need to ask in forum)
            print_help();
            break;
        }
    }
    for (int i = 1; i < argc; i++)
    {
        if (isFlag(argv[i + 1])) { // Check if value exists (next element is not a flag)

            return ERR_MISSING_ARG;
        }
        // Start Checking which Flags.
        if (strcmp(argv[i], "-p") == 0) { // "-p" operation flag
            if (p_raise) {

                return ERR_NUM_ARGS;
            }
            p_raise = 1;
            i++;
            if (strcmp(argv[i], "enc") == 0) {
                p_cmd->op = OP_ENC;
            }
            else if (strcmp(argv[i], "dec") == 0) {
                p_cmd->op = OP_DEC;
            }
            else if (strcmp(argv[i], "censor") == 0) {
                p_cmd->op = OP_CENSOR;
            }
            else {

                return ERR_BAD_OP;
            }
        }
        else if (strcmp(argv[i], "-t") == 0) { // "-t" encryption type flag
            if (t_raise) {

                return ERR_NUM_ARGS;
            }
            t_raise = 1;
            i++;
            int num = atoi(argv[i]);
            switch (num)
            {
            case 0:
                p_cmd->enc_type = ENC_TYPE_NONE;
                break;
            case 1:
                p_cmd->enc_type = ENC_TYPE_FLIP_EVEN;
                break;
            case 2:
                p_cmd->enc_type = ENC_TYPE_SWAP_3;
                break;
            case 3:
                p_cmd->enc_type = ENC_TYPE_ROT_AND_CENTER_5;
                break;
            default:
                p_cmd->enc_type = ENC_TYPE_LAST;
                break;
            }
            if (p_cmd->enc_type == ENC_TYPE_LAST) {

                return ERR_BAD_ENC_TYPE;
            }
        }
        else if (strcmp(argv[i], "-i") == 0) { // "-i" input path flag
            if (i_raise) {

                return ERR_NUM_ARGS;
            }
            i_raise = 1;
            p_cmd->input_path = argv[++i];
            
        }
        else if (strcmp(argv[i], "-o") == 0) { // "-o" output path flag
            if (o_raise) {

                return ERR_NUM_ARGS;
            }
            o_raise = 1;
            p_cmd->output_path = argv[++i];
            
        }
        else if (strcmp(argv[i], "-b") == 0) { // "-b" blacklist path flag
            if (b_raise) {

                return ERR_NUM_ARGS;
            }
            b_raise = 1;
            p_cmd->blacklist_path = argv[++i];
           
        }
        else {  // No Flag was found.

            return ERR_UNKNOWN_FLAG;
        }

    }
    if (argc < 2 * ENCRYPT_ARG_NUM + 1 || argc == 2 * ENCRYPT_ARG_NUM + 1 && b_raise == 1 || argc != 2 * CENSOR_ARG_NUM + 1 && p_cmd->op == OP_CENSOR) { // Not enough arguments

        return ERR_NUM_ARGS;
    }
  return OK;
}
