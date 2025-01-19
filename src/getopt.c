#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "ab:c::")) != -1) {
    switch (opt) {
      case 'a':
        printf("Option -a\n");
        break;
      case 'b':
        printf("Option -b with value '%s'\n", optarg);
        break;
      case 'c':
        printf("Option -c with value '%s'\n", optarg ? optarg : "none");
        break;
      case '?':
        printf("Unknown option: %c\n", optopt);
        break;
      default:
        fprintf(stderr, "Usage: %s [-a] [-b value] [-c[value]]\n", argv[0]);
        return 1;
    }
  }
  return 0;
}
