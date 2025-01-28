#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum {
  OPT_PRESERVE_CRED = CHAR_MAX + 1,
  OPT_KEEPCAPS,
  OPT_USER_PARENT,
};

int main(int argc, char *argv[]) {
  int opt;
  int preserve_cred = 0;
  int keepcaps = 0;
  int user_parent = 0;

  static struct option long_options[] = {
      {"preserve-credentials", no_argument, 0, OPT_PRESERVE_CRED},
      {"keepcaps", no_argument, 0, OPT_KEEPCAPS},
      {"user-parent", no_argument, 0, OPT_USER_PARENT},
      {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "", long_options, NULL)) != -1) {
    switch (opt) {
    case OPT_PRESERVE_CRED:
      preserve_cred = 1;
      break;
    case OPT_KEEPCAPS:
      keepcaps = 1;
      break;
    case OPT_USER_PARENT:
      user_parent = 1;
      break;
    default:
      fprintf(
          stderr,
          "Usage: %s [--preserve-credentials] [--keepcaps] [--user-parent]\n",
          argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  printf("Preserve Credentials: %d\n", preserve_cred);
  printf("Keep Capabilities: %d\n", keepcaps);
  printf("User Parent: %d\n", user_parent);

  return 0;
}