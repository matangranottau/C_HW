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
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h")) {  // "-h" help flag
            print_help();
            break;
        }
        printf("hello");
  return OK;
}
