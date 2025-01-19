#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("用法: %s [选项] [参数]\n", argv[0]);
    printf("选项:\n");
    printf("  -h, --help    显示帮助信息\n");
    printf("  -v, --version 显示版本信息\n");
    return 1;
  }

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printf("帮助信息: 这是一个命令行解析示例程序。\n");
    } else if (strcmp(argv[i], "-v") == 0 ||
               strcmp(argv[i], "--version") == 0) {
      printf("版本信息: v1.0.0\n");
    } else {
      printf("未知选项: %s\n", argv[i]);
    }
  }

  return 0;
}
