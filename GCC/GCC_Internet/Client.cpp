//
//  Client.cpp
//  GCC_Internet
//
//  Created by Niu Panfeng on 15/5/14.
//
//  可以在网络中发送大文件，厉害的很

#include "Client.h"

int main()
{
    cout<<"===========CLIENT===========\n";
    
    Client client;
    client.Init();
    client.ConnectServer("127.0.0.1",8001);
    //client.SendFile("FileForSend_Client.txt");
    client.SendFile("/Users/niupanfeng/Documents/百度云同步盘/MacBook Pro/图片/798/IMG_0007.CR2");
    client.DisConnectServer();
    
    return 0;
}
