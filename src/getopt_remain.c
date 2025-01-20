#include <getopt.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "ab:")) != -1) {
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

  // 获取剩余参数
  if (optind < argc) {
    printf("Remaining arguments:\n");
    for (int i = optind; i < argc; i++) {
      printf("  %s\n", argv[i]);
    }
  } else {
    printf("No remaining arguments.\n");
  }

  return 0;
}