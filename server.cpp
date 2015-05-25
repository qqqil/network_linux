#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <strings.h>

void str_echo(int sockfd){
    ssize_t n;
    char buf[MAXLINE];
    again:
    while((n=read(sockfd,buf,MAXLINE)) > 0) {
        write(sockfd,buf,n);
    }
    if(n<0 && errno == ENTER){
        goto again;
    }
    else if(n <0){
        printf("str_echo:read_error");
    }
}

int main(){

    int listenFd,connFd;
    pid_t childpid;
    socklen_t chilen;
    struct sockaddr_in childaddr,serverAddr;
    listenFd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&serverAddr,sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htol(INADDR_ANY);
    serverAddr.sin_port = htos(SERV_PORT);

    int ret = bind(listenFd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));

    listen(listenFd,16);

    while(true){
        clilen = sizeof(childaddr);
        connFd = accept(listenFd,(struct sockaddr *)&childaddr,&chilen);
        if((childpid = fork())==0){
            close(listenFd);
            str_echo(connFd);
            exit(0);
        }
        close(connFd);
    }
    close(listenFd);
}