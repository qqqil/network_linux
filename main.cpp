#include <iostream>


#include <sys/types.h>
#include <sys/socket.h>

#include <string>

#include <stdlib.h>

/* inet*/
#include <netinet/in.h>
#include <arpa/inet.h>


#include "logger.h"
#include "socket.h"



int main(int argc, char *argv[])
{
    Logger::info("create client..");
    class Socket server;

    struct sockaddr client_addr;

    socklen_t client_len;
    int client = server.start_accept(client_addr,client_len);
    if(client == -1){
        Logger::error("accept failed!");
        server.start_close();
        exit(-1);
    }

}
