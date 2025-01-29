#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
int main() {
  int server_fd, client_fd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  char buffer[BUFFER_SIZE];

  // 创建套接字
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // 绑定地址
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(TCP_PORT);

  if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) ==
      -1) {
    perror("bind");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  // 监听连接
  if (listen(server_fd, 10) == -1) {
    perror("listen");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port %d...\n", TCP_PORT);

  // 接受连接
  client_fd =
      accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
  if (client_fd == -1) {
    perror("accept");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  printf("Client connected.\n");

  // 接收数据
  ssize_t nread = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
  if (nread == -1) {
    perror("recv");
  } else {
    buffer[nread] = '\0';
    printf("Received: %s\n", buffer);

    // 发送数据
    send(client_fd, buffer, strlen(buffer), 0);
  }

  // 关闭套接字
  close(client_fd);
  close(server_fd);

  return 0;
}