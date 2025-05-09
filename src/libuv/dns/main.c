#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

uv_loop_t *loop;

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
  buf->base = malloc(suggested_size);
  buf->len = suggested_size;
}

void on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
  if (nread < 0) {
    if (nread != UV_EOF) fprintf(stderr, "read error %s\n", uv_err_name(nread));

    uv_close((uv_handle_t *)client, NULL);
    if (buf->base) free(buf->base);
    free(client);
    return;
  }
  if (nread == 0) {
    if (buf->base) free(buf->base);
    return;
  }

  char *data = (char *)malloc(sizeof(char) * (nread + 1));
  data[nread] = '\0';
  strncpy(data, buf->base, nread);
  fprintf(stderr, "%s", data);
  free(data);
  free(buf->base);
}

void on_connect(uv_connect_t *req, int status) {
  if (status < 0) {
    fprintf(stderr, "connect failed error: %s\n", uv_err_name(status));
    free(req);
    return;
  }

  uv_read_start((uv_stream_t *)req->handle, alloc_buffer, on_read);
}
void on_resolved(uv_getaddrinfo_t *resolver, int status, struct addrinfo *res) {
  if (status < 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", uv_strerror(status));
    return;
  }
  char addr[17] = {0};
  uv_ip4_name((struct sockaddr_in *)res->ai_addr, addr, 16);
  fprintf(stderr, "%s\n", addr);

  uv_connect_t *connect_req = (uv_connect_t *)malloc(sizeof(uv_connect_t));
  uv_tcp_t *socket = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
  uv_tcp_init(loop, socket);
  uv_tcp_connect(connect_req, socket, res->ai_addr, on_connect);
  uv_freeaddrinfo(res);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <domain>\n", argv[0]);
    return EXIT_FAILURE;
  }

  loop = uv_default_loop();

  struct addrinfo hints;
  hints.ai_family = PF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  uv_getaddrinfo_t resolver;
  fprintf(stderr, "Resolving...\n");
  int r = uv_getaddrinfo(loop, &resolver, on_resolved, argv[1], "80", &hints);
  if (r) {
    fprintf(stderr, "getaddrinfo error: %s\n", uv_strerror(r));
    return 1;
  }

  return uv_run(loop, UV_RUN_DEFAULT);
}