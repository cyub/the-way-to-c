#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
int main() {
  int client_fd;
  struct sockaddr_in server_addr;
  char buffer[BUFFER_SIZE];

  // 创建套接字
  client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (client_fd == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // 设置服务器地址
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(TCP_PORT);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // 连接到服务器
  if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) ==
      -1) {
    perror("connect");
    close(client_fd);
    exit(EXIT_FAILURE);
  }

  printf("Connected to server.\n");

  // 发送数据
  const char* message = "Hello, server!";
  send(client_fd, message, strlen(message), 0);

  // 接收数据
  ssize_t nread = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
  if (nread == -1) {
    perror("recv");
  } else {
    buffer[nread] = '\0';
    printf("Received: %s\n", buffer);
  }

  // 关闭套接字
  close(client_fd);

  return 0;
}