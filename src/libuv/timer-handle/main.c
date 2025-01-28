#include <stdio.h>
#include <uv.h>

void on_timer(uv_timer_t* handle) { printf("Timer triggered!\n"); }

int main() {
  uv_loop_t* loop = uv_default_loop();

  uv_timer_t timer;
  uv_timer_init(loop, &timer);                   // 初始化 Handle
  uv_timer_start(&timer, on_timer, 1000, 2000);  // 1秒后启动，每2秒触发一次

  uv_run(loop, UV_RUN_DEFAULT);  // 运行事件循环

  uv_close((uv_handle_t*)&timer, NULL);  // 关闭 Handle
  return 0;
}