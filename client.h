#ifndef CLIENT_H
#define CLIENT_H

#include "socket.h"
class Client
{
public:
    Client();
    ~Client();
    int connect(string ip);
    string read();
    int write(string data);
    Socket getSock();
private:
    class Socket sock;
};

#endif // CLIENT_H
