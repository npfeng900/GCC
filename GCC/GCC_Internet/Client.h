//
//  Client.h
//  GCC_Internet
//
//  Created by Niu Panfeng on 15/5/14.
//
//

#ifndef __GCC_Internet__Client__
#define __GCC_Internet__Client__

#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_pton
#include <fstream>
#include "Frame.h"

using namespace std;

#define BUFFER_SIZE 2048
string str_end="END_OF_CLIENT_FILE_FOR_SEND";

class Client
{
private:
    int socket_fd;
public:
    Client(){};
    ~Client(){};
    int Init();
    int ConnectServer(const char* server_strIP,int server_port);
    int DisConnectServer();
    int SendBuffer(const char* buffer,int size);
    int SendFile(const char* filename);
};

int Client::Init()
{
    // 声明并初始化一个客户端的socket地址结构
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = htons(INADDR_ANY);
    client_addr.sin_port = htons(0);
    
    // 创建socket，若成功，返回socket描述符
    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        cout<<"Create Socket Failed!\n";
        return -1;
    }
    
    // 绑定客户端的socket和客户端的socket地址结构 非必需
    if(-1 == (bind(socket_fd, (struct sockaddr*)&client_addr, sizeof(client_addr))))
    {
        cout<<"Client Bind Failed!\n";
        return -1;
    }
    
    return 0;
}

int Client::ConnectServer(const char* server_strIP,int server_port)
{
    // 声明一个服务器端的socket地址结构，并用服务器那边的IP地址及端口对其进行初始化，用于后面的连接
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if(inet_pton(AF_INET, server_strIP, &server_addr.sin_addr) == 0)
    {
        cout<<"Server IP Address Error\n";
        return -1;
    }
    
    
    // 向服务器发起连接，连接成功后client_socket_fd代表了客户端和服务器的一个socket连接
    socklen_t server_addr_length = sizeof(server_addr);
    if(connect(socket_fd, (struct sockaddr*)&server_addr, server_addr_length) < 0)
    {
        cout<<"Can Not Connect To Server IP\n";
        return -1;
    }

    return 0;
}

int Client::DisConnectServer()
{
    if(close(socket_fd)!=0)
    {
        cout<<"DisConnect Server Error\n";
    };
    return 0;
}

int Client::SendBuffer(const char* buffer,int size)
{
    if(send(socket_fd, buffer, size, 0) < 0)
    {
        cout<<"Send Data Error！\n";
        return -1;
    }
    return 0;
}

int Client::SendFile(const char* filename)
{
    // 读取待发送的文件，分包存入buffer依次发送
    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);
    ifstream file_in;
    
    // 打开待发送的文件
    file_in.open(filename,ios::in|ios::binary);
    if(!file_in)
    {
        cout<<"Open file \""<<filename<<"\" Error\n";
        return -1;
    }
    
    // 分包发送文件的内容
    // 知道文件的末尾位置
    int pos,pos_end;
    file_in.seekg(0,ios::end);//一到文件末尾位置
    pos_end=file_in.tellg();
    file_in.seekg(0,ios::beg);//回到文件开始位置
    pos=file_in.tellg();
    
    FrameHeader *pframeHeader=new FrameHeader();//帧头标识
    pframeHeader->frame_No=0;      //帧序号初始化为0
    int data_max_size=BUFFER_SIZE-sizeof(FrameHeader);//数据区的最大长度
    
    while (pos<pos_end)
    {
        if((pos_end-pos) > data_max_size)
            pframeHeader->len=data_max_size;
        else
            pframeHeader->len=pos_end-pos;
        
        memcpy(buffer,pframeHeader,sizeof(FrameHeader));
        file_in.read(buffer+sizeof(FrameHeader),pframeHeader->len);
        SendBuffer(buffer,BUFFER_SIZE);
        pos=file_in.tellg();
        pframeHeader->frame_No++;
    }
    
    //发送结尾标识
    SendBuffer(str_end.c_str(), str_end.length());
    
    file_in.close();
    
    return 0;
}

#endif /* defined(__GCC_Internet__Client__) */
