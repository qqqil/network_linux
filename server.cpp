#include "server.h"
#include <time.h>

#include "clockutils.h"
#include "select.h"


Server::Server()
{
    sock.setSock(sock.create_and_listen(sock.getIp()));
}

int Server::start_service(sockaddr_in& addr, socklen_t& len)
{
    return sock.start_accept(addr,len);
}

string Server::read(int fd)
{
    return sock.read(fd);
}

int Server::write(string data)
{
    return sock.write(data);
}
Socket& Server::getSocket(){
    return sock;
}
#define SELECT

int main(){
    Logger::info("server start..");
    class Server server;

    struct sockaddr_in client_addr;

    socklen_t client_len;
    ClockUtils clock;
    clock.start();
    int count =0 ;
    int maxfds =FD_SETSIZE ;
    Select select;
    select.zero(select.get_rset());
    select.zero(select.get_wset());
    select.zero(select.get_exp_set());
    int server_fd = server.getSocket().getSock();
    select.set(server.getSocket().getSock(),select.get_rset());
    for(int i=0;i<10;i++){
#ifdef NORM
        int client = server.start_service(client_addr,client_len);
        if(client == -1){
            Logger::error("accept failed!");
            exit(-1);
        }
        string msg = inet_ntoa(client_addr.sin_addr);
        Logger::info("accept client:"+ msg+" - "+std::to_string(count++));
        string data;
        data = server.read(client);
        Logger::info(data);
        close(client);
#endif
#ifdef SELECT
    Logger::info("-0-");
    fd_set active_set;
    std::cout<<server.getSocket().getSock()<<std::endl;
    FD_ZERO(&active_set);
    //FD_SET(server_fd,&active_set);
    //std::cout<<"server fd ="<<server_fd<<std::endl;
    int ret =-1;//= ::select(FD_SETSIZE,&active_set,NULL,NULL,NULL);
    Logger::info("-1-");
    ret = select.select(maxfds);
    if(ret == -1){
        Logger::error("select error");
        continue;
    }
    for(int i =0;i<maxfds;i++){
           if(select.is_set(i,select.get_rset())){
                if(i == server.getSocket().getSock()){
                    int client = server.start_service(client_addr,client_len);
                    if(client == -1){
                        Logger::error("accept failed!");
                        continue;
                    }
                    Logger::info("accept a new connection..");
                    std::cout<<client<<std::endl;
                    select.set(client,select.get_rset());
                }else{
                    Logger::info("receive data ..");
                    string data = server.read(i);
                    Logger::info(data);
                    close(i);
                    select.clear(i,select.get_rset());
                }
           }
    }
    //select.set_rset(active_set);
#endif
    }
    clock.end();
    std::cout<<"Duration:"<<clock.getDuration()<<std::endl;
}
