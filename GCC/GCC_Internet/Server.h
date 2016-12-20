//
//  Server.h
//  GCC_Internet
//
//  Created by Niu Panfeng on 15/5/14.
//
//

#ifndef __GCC_Internet__Server__
#define __GCC_Internet__Server__

#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fstream>
#include "Frame.h"

using namespace std;

#define SERVER_PORT 8001
#define BUFFER_SIZE 2048
string str_end="END_OF_CLIENT_FILE_FOR_SEND";

class Server
{
private:
    int socket_fd;
public:
    Server(){};
    ~Server(){};
    int Init(int server_port,int size_listen);
    int Close();
    int Receive(const char* filename);
};

int Server::Init(int server_port,int size_listen)
{
    // 声明并初始化一个服务器端的socket地址结构
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htons(INADDR_ANY);
    server_addr.sin_port=htons(server_port);
    
    // 创建socket，若成功，返回socket描述符
    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        cout<<"Create Socket Failed!\n";
        return -1;
    }
    int opt = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // 绑定socket和socket地址结构
    if(-1 == bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)))
    {
        cout<<"Server Bind Failed!\n";
        return -1;
    }
    
    // socket监听
    if(0 != listen(socket_fd, size_listen))
    {
        cout<<"Server Listen Failed!\n";
        return -1;
    }
    
    return 0;
}

int Server::Close()
{
    if(close(socket_fd)!=0)
    {
        cout<<"DisConnect Server Error\n";
    };
    return 0;
}

int Server::Receive(const char* filename)
{
    while(1)
    {
        // 定义客户端的socket地址结构
        struct sockaddr_in client_addr;
        socklen_t client_addr_length = sizeof(client_addr);
        
        // 接受连接请求，返回一个新的socket(描述符)，这个新socket用于同连接的客户端通信
        // accept函数会把连接到的客户端信息写到client_addr中
        int new_server_socket_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &client_addr_length);
        if(new_server_socket_fd < 0)
        {
            cout<<"Server Accept Failed!\n";
            break;
        }
        else
        {
            cout<<"Server Accept a client!\n";
        }
        
        // recv函数接收数据到缓冲区buffer中
        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);
        FrameHeader *pframeHeader;//用于读取帧头信息
        
        ofstream file_out;
        file_out.open(filename,ios::out|ios::binary);
        
        while(1)
        {
            if(recv(new_server_socket_fd, buffer, BUFFER_SIZE, 0) < 0)
            {
                cout<<("Server Recieve Data Failed: Recieve Again!!\n");
                continue;
            }

            if (!strcmp(buffer,str_end.c_str()))
            {
                break;
            }
            else
            {
                pframeHeader=(FrameHeader*)buffer;
                file_out.write(buffer+sizeof(FrameHeader),pframeHeader->len);
            }
            //file_out.write(buffer,BUFFER_SIZE);
            bzero(buffer, BUFFER_SIZE);
        }
        
        // 关闭与客户端的连接
        close(new_server_socket_fd);
        cout<<"Server Disconnect a client!\n";
    }
    
    return 0;
}

#endif /* defined(__GCC_Internet__Server__) */
