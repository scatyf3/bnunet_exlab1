// http.c

#include "http.h"

// 请完成这个函数
// 这个函数的参数是一个字符串，表示原始的请求，你可以用printf打印看看是啥
// 这个函数的返回值是response，表示输出的响应，你需要按照格式来自行构造
// 理论上，你写完这个函数，编译运行，能通过访问 http://127.0.0.1 来交互
// 你可以尝试着让你写的函数去访问htdocs里面的网页，方法是通过读取文件
// 如果你不会写，可以试试最暴力地方法，先自己构造一个静态的response在浏览器里看看效果
// 如果你实在不会，可以在answer文件夹里参考答案，然后自己独立实现出来
char *http_process(char *request) {
  static char response[1024]; // 如果1024不够用你还可以自己添加
  *response = '\0';
  

  return response;
}
