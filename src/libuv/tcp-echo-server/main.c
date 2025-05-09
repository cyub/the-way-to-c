#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

#define DEFAULT_PORT 7000
#define DEFAULT_BACKLOG 128
struct sockaddr_in addr;

uv_loop_t *loop;

typedef struct {
  uv_write_t req;
  uv_buf_t buf;
} write_req_t;

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
  buf->base = (char *)malloc(suggested_size);
  buf->len = suggested_size;
}

void on_close(uv_handle_t *handle) { free(handle); }

void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
  if (nread > 0) {
    write_req_t *req = (write_req_t *)malloc(sizeof(write_req_t));
    printf("Received: %.*s\n", (int)nread, buf->base);
    req->buf = uv_buf_init(buf->base, nread);
    uv_write((uv_write_t *)req, client, &req->buf, 1, NULL);
    return;
  }
  if (nread < 0) {
    if (nread != UV_EOF) fprintf(stderr, "Read error %s\n", uv_err_name(nread));
    uv_close((uv_handle_t *)client, NULL);
  }

  if (buf->base) free(buf->base);
}

void on_new_connection(uv_stream_t *server, int status) {
  if (status < 0) {
    fprintf(stderr, "New connection error %s\n", uv_strerror(status));
  }

  uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
  uv_tcp_init(loop, client);
  if (uv_accept(server, (uv_stream_t *)client) == 0) {
    uv_read_start((uv_stream_t *)client, alloc_buffer, echo_read);
  } else {
    uv_close((uv_handle_t *)client, on_close);
  }
}

int main(int argc, char *argv[]) {
  loop = uv_default_loop();
  uv_tcp_t server;
  uv_tcp_init(loop, &server);

  uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);
  uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);

  int r = uv_listen((uv_stream_t *)&server, DEFAULT_BACKLOG, on_new_connection);

  if (r) {
    fprintf(stderr, "Listen error %s\n", uv_strerror(r));
    return 1;
  }

  return uv_run(loop, UV_RUN_DEFAULT);
}