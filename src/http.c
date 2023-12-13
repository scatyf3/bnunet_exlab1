// http.c

#include "http.h"

// 请完成这个函数
// 这个函数的参数是一个字符串，表示原始的请求，你可以用printf打印看看是啥
// 这个函数的返回值是response，表示输出的响应，你需要按照格式来自行构造
// 理论上，你写完这个函数，编译运行，能通过访问 http://127.0.0.1 来交互
// 你可以尝试着让你写的函数去访问htdocs里面的网页，方法是通过读取文件
// 如果你不会写，可以试试最暴力地方法，先自己构造一个静态的response在浏览器里看看效果
// 如果你实在不会，可以在answer文件夹里参考答案，然后自己独立实现出来
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tcp.h"

char *http_process(char *request) {
  static char response[1024];
  *response = '\0';
  char path[1024];
  sscanf(request, "GET %s", path);
  char file_path[1024];
  sprintf(file_path, "htdocs%s", path);
  FILE *file = fopen(file_path, "rb");
  if (file) {
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *file_content = malloc(file_size + 1);
    fread(file_content, file_size, 1, file);
    file_content[file_size] = '\0';
    sprintf(response, "HTTP/1.1 200 OK\r\n");
    strcat(response, "Content-Type: text/html\r\n");
    strcat(response, "\r\n");
    strcat(response, file_content);
    free(file_content);
    fclose(file);
  } else {
    // 404 response todo
    sprintf(response, "HTTP/1.1 404 Not Found\r\n");
    strcat(response, "Content-Type: text/html\r\n");
    strcat(response, "\r\n");
    strcat(response, "<html><body><h1>404 Not Found</h1></body></html>");
  }

  return response;
}