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

string Client::read()
{
    return sock.read(sock.getSock());
}

int Client::write(string data)
{
    return sock.write(data);
}

Socket Client::getSock(){
    return sock;
}

int main(){

    Logger::info("client start to connect..");
    for(int i=0;i<1000;i++){
        Client client;
        string ip="192.168.1.101";

        int ret = client.connect(ip);

        if(ret == -1){
            Logger::error("connect filed!");
            exit(1);
        }
        client.write("hello ,girl!");
        string ss;
        ss = client.read();
        Logger::info("Receive data from server :"+ss);
        std::cout<<"For :";
        std::cout<<i;
        std::cout<<" times";
        std::cout<<std::endl;
        ThreadUtils::sleep(100);
    }
}
