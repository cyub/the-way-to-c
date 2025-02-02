#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#define PORT 7000
#define MESSAGE "Hello, libuv!"

uv_loop_t *loop;
uv_tcp_t client;
uv_connect_t connect_req;
uv_write_t write_req;

void on_write(uv_write_t *req, int status) {
  if (status) {
    fprintf(stderr, "Write error %s\n", uv_strerror(status));
  }
  free(req->data);
  uv_close((uv_handle_t *)req->handle, NULL);  // 发送完成后关闭连接
}

void on_connect(uv_connect_t *req, int status) {
  if (status < 0) {
    fprintf(stderr, "Connect error %s\n", uv_strerror(status));
    return;
  }

  uv_buf_t buffer = uv_buf_init(strdup(MESSAGE), strlen(MESSAGE));
  write_req.data = buffer.base;
  uv_write(&write_req, req->handle, &buffer, 1, on_write);
}

int main() {
  loop = uv_default_loop();
  uv_tcp_init(loop, &client);

  struct sockaddr_in server_addr;
  uv_ip4_addr("127.0.0.1", PORT, &server_addr);

  uv_tcp_connect(&connect_req, &client, (const struct sockaddr *)&server_addr,
                 on_connect);

  return uv_run(loop, UV_RUN_DEFAULT);
}