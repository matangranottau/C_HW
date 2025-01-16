#define _CRT_SECURE_NO_WARNINGS
#include "parser.h"
#include "error_types.h"
#include <stdio.h>
#include <string.h>
#define FLAGS_LEN(flags) (sizeof(flags) / sizeof(flag_t))

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

void print_help() {
  printf("Usage:\n");
  for (int i = 0; i < FLAGS_LEN(flags); i++) {
    printf("%*s%*s: %s,\n", 4, flags[i].short_name, 17, flags[i].long_name,
           flags[i].description);
  }
  printf("Please try again.\n");
}

int parse_args(int argc, const char *argv[], command_t *p_cmd) {
  // TODO
    // TODO: Check First Valid!!
    for (int j = 1; j < argc; j++) {
        if (strcmp(argv[j], "-h") == 0) {  // "-h" help flag (need to ask in forum)
            print_help();
            break;
        }
    }
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-p") == 0) { // "-p" operation flag
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
        }
        else if (strcmp(argv[i], "-t") == 0) {
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
        }
        else if (strcmp(argv[i], "-i") == 0) {
            p_cmd->input_path = argv[++i];
            //printf("%s\n", p_cmd->input_path);
        }
        else if (strcmp(argv[i], "-o") == 0) {
            p_cmd->output_path = argv[++i];
            //printf("%s\n", p_cmd->output_path);
        }
        else if (strcmp(argv[i], "-b") == 0) {
            p_cmd->blacklist_path = argv[++i];
            //printf("%s\n", p_cmd->blacklist_path);
        }
        else {
            return ERR_UNKNOWN_FLAG;
        }
    }
  return OK;
}
