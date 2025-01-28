#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <uv.h>

uv_fs_t open_req;
uv_fs_t read_req;
uv_fs_t write_req;

static uint8_t buffer[1024];

static uv_buf_t iov;

void on_read(uv_fs_t *req);

void on_write(uv_fs_t *req) {
  if (req->result < 0) {
    fprintf(stderr, "Write error: %s\n", uv_strerror((int)req->result));
  } else {
    uv_fs_read(uv_default_loop(), &read_req, open_req.result, &iov, 1, -1,
               on_read);
  }
}

void on_read(uv_fs_t *req) {
  assert(req == &read_req);
  if (req->result < 0) {
    fprintf(stderr, "Read error: %s\n", uv_strerror(req->result));
  } else if (req->result == 0) {
    uv_fs_t close_req;
    uv_fs_close(uv_default_loop(), &close_req, open_req.result,
                NULL);  // 没有注册回调，us_fs_close会同步执行
  } else if (req->result > 0) {  // req->result记录读取内容长度
    iov.len = req->result;
    uv_fs_write(uv_default_loop(), &write_req, 1, &iov, 1, -1, on_write);
  }
}

void on_open(uv_fs_t *req) {
  assert(req == &open_req);

  if (req->result >= 0) {  // req->result指向文件描述符
    iov = uv_buf_init((char *)buffer, sizeof(buffer));
    // nbufs 为 1：表示只使用一个缓冲区（iov）
    // offset 为 -1：表示从文件的当前位置开始读取
    uv_fs_read(uv_default_loop(), &read_req, req->result, &iov, 1, -1, on_read);
  } else {
    fprintf(stderr, "error opening file: %s\n", uv_strerror(req->result));
  }
}

int main(int argc, char *argv[]) {
  uv_fs_open(uv_default_loop(), &open_req, argv[1], O_RDONLY, 0, on_open);
  uv_run(uv_default_loop(), UV_RUN_DEFAULT);
  uv_fs_req_cleanup(&open_req);
  uv_fs_req_cleanup(&read_req);
  uv_fs_req_cleanup(&write_req);
}