#include "client.h"
#include "logger.h"
#include "threadutils.h"
#include <iostream>

Client::Client()
{

}

Client::~Client()
{ 
    //

}

int Client::connect(string ip)
{
    struct sockaddr_in server_addr;
        sock.build_socket(server_addr,ip);
    int ret = sock.connect(server_addr);
    if(ret == -1){
        Logger::error("connect to server failed!");
    }
    
    return ret;
}

string Client::read(int fd)
{
    return sock.read(fd);
}

int Client::write(string data)
{
    return sock.write(data);
}

int main(){

    Logger::info("clien start to connect..");
    for(int i=0;i<10;i++){
        Client client;
        string ip="192.168.1.101";

        int ret = client.connect(ip);

        if(ret == -1){
            Logger::error("connect filed!");
            exit(1);
        }
        client.write("hello ,girl!");
        ThreadUtils::sleep(100);
    }
}
