#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

void on_read(uv_fs_t* req);
void on_write(uv_fs_t* req);

uv_fs_t open_req;
uv_fs_t read_req;
uv_fs_t write_req;
uv_fs_t close_req;

uv_buf_t iov;
char buffer[1024];

void on_open(uv_fs_t* req) {
  if (req->result < 0) {
    fprintf(stderr, "Error opening file: %s\n", uv_strerror(req->result));
    return;
  }
  printf("File opened successfully.\n");

  // 读取文件
  iov = uv_buf_init(buffer, sizeof(buffer));
  uv_fs_read(uv_default_loop(), &read_req, req->result, &iov, 1, -1, on_read);
}

void on_read(uv_fs_t* req) {
  if (req->result < 0) {
    fprintf(stderr, "Error reading file: %s\n", uv_strerror(req->result));
    return;
  }
  printf("File read successfully.\n");

  // 关闭读取的文件
  uv_fs_close(uv_default_loop(), &close_req, open_req.result, NULL);

  // 打开目标文件
  uv_fs_open(uv_default_loop(), &open_req, "output.txt", O_WRONLY | O_CREAT,
             0644, on_write);
}

void on_write(uv_fs_t* req) {
  if (req->result < 0) {
    fprintf(stderr, "Error opening output file: %s\n",
            uv_strerror(req->result));
    return;
  }
  printf("Output file opened successfully.\n");

  // 写入数据
  uv_fs_write(uv_default_loop(), &write_req, req->result, &iov, 1, -1, NULL);
  printf("Data written to output file.\n");

  // 关闭目标文件
  uv_fs_close(uv_default_loop(), &close_req, req->result, NULL);
}

int main() {
  // 初始化事件循环
  uv_loop_t* loop = uv_default_loop();

  // 打开文件
  uv_fs_open(loop, &open_req, "input.txt", O_RDONLY, 0, on_open);

  // 运行事件循环
  uv_run(loop, UV_RUN_DEFAULT);

  // 清理请求
  uv_fs_req_cleanup(&open_req);
  uv_fs_req_cleanup(&read_req);
  uv_fs_req_cleanup(&write_req);
  uv_fs_req_cleanup(&close_req);

  return 0;
}