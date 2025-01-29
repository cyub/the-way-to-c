#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
int main() {
  int sockfd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  char buffer[BUFFER_SIZE];

  // 创建UDP套接字
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  // 初始化服务器地址
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(UDP_PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // 绑定套接字到地址
  if (bind(sockfd, (const struct sockaddr*)&server_addr, sizeof(server_addr)) <
      0) {
    perror("bind failed");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  printf("UDP server is listening on port %d...\n", UDP_PORT);

  while (1) {
    // 接收数据
    ssize_t nread = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
                             (struct sockaddr*)&client_addr, &client_addr_len);
    if (nread < 0) {
      perror("recvfrom failed");
      continue;
    }

    buffer[nread] = '\0';  // 确保字符串结尾
    printf("Received message: %s\n", buffer);

    // 回显数据给客户端
    if (sendto(sockfd, buffer, nread, 0, (const struct sockaddr*)&client_addr,
               client_addr_len) < 0) {
      perror("sendto failed");
    }
  }

  // 关闭套接字
  close(sockfd);
  return 0;
}