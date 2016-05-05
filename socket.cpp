#include "socket.h"



Socket::Socket()
{
    Logger::info("create socket");
}

Socket::~Socket()
{
    ::close(sock);
    Logger::info("close socket");
}

int Socket::create_and_listen(string ip)
{
    struct sockaddr_in addr;
    build_socket(addr,ip);

    int ret = bind(sock,(const struct sockaddr*)&addr,
                   sizeof(addr));
    if(ret == -1){
        Logger::error("bind ip failed!");
        exit(-1);
    }
    if(setsockopt(sock,SOL_SOCKET,(SO_REUSEPORT | SO_REUSEADDR),NULL,0)==-1){
        Logger::error("set socket option failed!");
    }
    ret = listen(sock, max_clients);
    if(ret == -1){
        Logger::error("listen to sock failed!");
        exit(-1);
    }
    std::cout<<"sock = " <<sock<<std::endl;
    return sock;
}
/**
 * @brief Socket::accept accept client connection
 * @param client_addr
 * @param client_len
 * @param flag
 * @return
 */
int Socket::start_accept(sockaddr_in& client_addr, socklen_t client_len)
{
    return ::accept(sock,(struct sockaddr*)&client_addr,&client_len);
}

int Socket::build_socket(sockaddr_in& addr, string ip)
{
    sock = ::socket(AF_INET,SOCK_STREAM,0);
    if(sock == -1){
        Logger::error("create socket failed!");
        exit(1);
    }
//    struct sockaddr_in sock_addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    inet_aton(ip.c_str(),&addr.sin_addr);

    return sock;
}

int Socket::connect(const sockaddr_in& addr)
{
    return ::connect(sock,(const sockaddr*)&addr,sizeof(addr));
}


int Socket::start_close()
{
    return ::close(sock);
}
string Socket::getIp() const
{
    return ip;
}

string Socket::read(int fd)
{
    int num =0;
    string str;
    while((num =::read(fd,buff,1024)) >0){
        for(int i=0;i<num;i++){
            str+=buff[i];
        }
        Logger::info("DATA:"+str);
    }
    Logger::info("DATA:"+str);

    return str;
}

int Socket::write(string data)
{
    size_t num = ::write(sock,data.c_str(),data.size());
    string msg;
    msg +=data;
    Logger::info("WRITE:"+ msg);
    return num;
}
int Socket::getSock() const
{
    return sock;
}

void Socket::setSock(int value)
{
    sock = value;
}

void Socket::make_noblock(int fd)
{

}



