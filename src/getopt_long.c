#include <getopt.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  int opt;
  int option_index = 0;
  static struct option long_options[] = {{"help", no_argument, 0, 'h'},
                                         {"output", required_argument, 0, 'o'},
                                         {"verbose", no_argument, 0, 'v'},
                                         {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "ho:v", long_options, &option_index)) !=
         -1) {
    switch (opt) {
      case 'h':
        printf("Help message\n");
        break;
      case 'o':
        printf("Output file: %s\n", optarg);
        break;
      case 'v':
        printf("Verbose mode enabled\n");
        break;
      case '?':
        printf("Unknown option\n");
        break;
      default:
        fprintf(stderr, "Usage: %s [-h] [-o file] [--verbose]\n", argv[0]);
        return 1;
    }
  }
  return 0;
}