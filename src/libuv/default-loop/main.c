#include <stdio.h>
#include <uv.h>

int main(int argc, char *argv[]) {
  uv_loop_t *loop = uv_default_loop();
  printf("Default loop.\n");

  uv_run(loop, UV_RUN_DEFAULT);
  uv_loop_close(loop);
  return 0;
}