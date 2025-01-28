#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

void on_read(uv_fs_t* req) {
  if (req->result < 0) {
    fprintf(stderr, "Read error: %s\n", uv_strerror(req->result));
  } else {
    printf("Data: %s\n", (char*)req->data);
  }
  uv_fs_req_cleanup(req);  // 清理 Request
}

int main() {
  uv_loop_t* loop = uv_default_loop();

  uv_fs_t read_req;
  uv_fs_open(loop, &read_req, "test.txt", O_RDONLY, 0, NULL);  // 打开文件
  uv_fs_read(loop, &read_req, read_req.result, (uv_buf_t*)malloc(1024), 1, -1,
             on_read);  // 读取文件

  uv_run(loop, UV_RUN_DEFAULT);  // 运行事件循环
  return 0;
}