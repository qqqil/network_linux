#ifndef SOCKET_H
#define SOCKET_H
#include <sys/types.h>
#include <sys/socket.h>

#include <string>

#include <stdlib.h>

/* inet*/
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "logger.h"

class Socket
{
public:
    Socket();
    ~Socket();
    int create_and_listen(string ip);
    int start_accept(struct sockaddr_in& client_addr,socklen_t client_len);
    int build_socket(struct sockaddr_in& addr,string ip);
    int connect(const sockaddr_in& addr);
    int start_close();
    string getIp() const;
    string read(int fd);
    int write(string data);

    int getSock() const;
    void setSock(int value);

private:
    void make_noblock(int fd);
    const string ip = "192.168.1.101";
    const int max_clients = 16;
    int sock;
    char buff[1024];
};

#endif // SOCKET_H
