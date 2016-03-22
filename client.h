#ifndef CLIENT_H
#define CLIENT_H

#include "socket.h"
class Client
{
public:
    Client();
    ~Client();
    int connect(string ip);
    string read(int fd);
    int write(string data);
private:
    class Socket sock;
};

#endif // CLIENT_H
