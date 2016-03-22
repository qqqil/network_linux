#ifndef SERVER_H
#define SERVER_H

#include "socket.h"

class Server
{
public:
    Server();
    int start_service(struct sockaddr_in& addr, socklen_t& len);
    string read(int fd);
    int write(string data);
    Socket& getSocket();
private:
    Socket sock;
};

#endif // SERVER_H
