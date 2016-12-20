//
//  Server.cpp
//  GCC_Internet
//
//  Created by Niu Panfeng on 15/5/14.
//
//

#include "Server.h"

int main()
{
    cout<<"===========SERVER===========\n";
    
    Server server;
    server.Init(SERVER_PORT,4);
    server.Receive("2.CR2");
    server.Close();
    
    return 0;
}