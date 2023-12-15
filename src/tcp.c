// tcp.c

#include "tcp.h"

SOCKET socketServer;

//处理关闭连接，即如果检测到SIGINT，即清理套接字相关的资源，终止通信
void sig_handler(int sig) {
  if(sig == SIGINT) {
    printf("connection close");
    closesocket(socketServer);
    WSACleanup();
    printf("[Info] Close socket listening.\r\n");
    exit(0);
  }
}

int tcp() {
  WSADATA wsaData;
  SOCKADDR_IN addrServer;
  SOCKET socketClient;
  SOCKADDR_IN addrClient;

  int addrlen = sizeof(SOCKADDR);
  char recvBuf[RECV_BUFFER_LENGTH];
  char *sendBuf;

  //初始化Winsock库，指定使用的版本为2.2
  WSAStartup(MAKEWORD(2, 2), &wsaData);
  //创建一个TCP套接字，并将其赋值给socketServer
  socketServer = socket(AF_INET, SOCK_STREAM, 0);
  //将服务器套接字绑定到本地的IP地址，这里使用0.0.0.0表示绑定到所有可用的网络接口
  addrServer.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");
  addrServer.sin_family = AF_INET; // IPv4
  addrServer.sin_port = htons(80); //Port 80
  bind(socketServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
  
  if(listen(socketServer, BACKLOG_LENGTH) == 0) {
    printf("[Info] Start to listen 0.0.0.0:80\r\n");
    signal(SIGINT, sig_handler);//注册SIGINT信号的处理函数，即按下Ctrl+C时执行的函数。
    while(1) {
      //接受客户端的连接请求，返回一个新的套接字socketClient用于与客户端通信
      socketClient = accept(socketServer, (SOCKADDR*)&addrClient, &addrlen);
      if(socketClient != -1) {
        recv(socketClient, recvBuf, RECV_BUFFER_LENGTH, 0); 
        sendBuf = http_process(recvBuf);
        if(sendBuf) {
          send(socketClient, sendBuf, strlen(sendBuf), 0);
        }
        closesocket(socketClient);
      }
    }
  } else {
    printf("[Error] Cannot listen.\r\n");
  }
  return 0;
}
