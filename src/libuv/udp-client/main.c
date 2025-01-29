#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"

int main() {
  int sockfd;
  struct sockaddr_in server_addr;
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
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // 发送数据到服务器
  const char* message = "Hello, server!";
  if (sendto(sockfd, message, strlen(message), 0,
             (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    perror("sendto failed");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  printf("Message sent: %s\n", message);

  // 接收服务器的回显数据
  socklen_t server_addr_len = sizeof(server_addr);
  ssize_t nread = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
                           (struct sockaddr*)&server_addr, &server_addr_len);
  if (nread < 0) {
    perror("recvfrom failed");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  buffer[nread] = '\0';  // 确保字符串结尾
  printf("Received echo: %s\n", buffer);

  // 关闭套接字
  close(sockfd);
  return 0;
}