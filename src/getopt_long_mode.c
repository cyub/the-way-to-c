#include <getopt.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
  int opt;
  while ((opt = getopt_long(argc, argv, "+ab:", NULL, NULL)) != -1) {
    switch (opt) {
      case 'a':
        printf("Option -a\n");
        break;
      case 'b':
        printf("Option -b with value '%s'\n", optarg);
        break;
      case '?':
        printf("Unknown option: %c\n", optopt);
        break;
      default:
        fprintf(stderr, "Usage: %s [-a] [-b value]\n", argv[0]);
        return 1;
    }
  }

  // 打印剩余的非选项参数
  for (int i = optind; i < argc; i++) {
    printf("Non-option argument: %s\n", argv[i]);
  }

  return 0;
}