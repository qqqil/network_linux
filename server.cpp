#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <strings.h>


#include "constant.h"



void log(char * str){
    printf("%s\n",str);
}
void str_echo(int sockfd){
    ssize_t n;
    char buf[MAXLINE];
    char str[1024];
    log("child process server for connect\n");
    again:
    bzero(buf,sizeof(buf));
    while((n=recv(sockfd,buf,sizeof(buf),0)) > 0) {
        log(buf);
        sprintf(str,"recvd data: %s\n","data from server");
        log(str);
        write(sockfd,buf,n);
        bzero(buf,sizeof(buf));//clear recieved data from the buffer 
    }
    log("read data finished!\n");
    if(n<0 && errno == EINTR){
        goto again;
    }
    else if(n <0){
        printf("str_echo:read_error");
    }
    close(sockfd);
    log("close client connection\n");
}

int main(){
    int listenFd,connFd;
    pid_t childpid;
    socklen_t chilen;
    struct sockaddr_in childaddr,serverAddr;
    char str[1024];
    bzero(str,sizeof(str));
    listenFd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&serverAddr,sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(SERV_PORT);

    int ret = bind(listenFd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
    if(ret == -1){
        printf("bind to port failed!\n");
        exit(1);
    }
    sprintf(str,"listen to port %d\n",SERV_PORT);
    log(str);
    ret = listen(listenFd,16);
    if(ret == -1){
        printf("listen to fd failed for %s\n",strerror(errno));
        return 1;
    }
    while(true){
        chilen = sizeof(childaddr);
        connFd = accept(listenFd,(struct sockaddr *)&childaddr,&chilen);
        sprintf(str,"accept from client for client fd: %d\n",connFd);
        log(str);
        if((childpid = fork())==0){
            close(listenFd);
            str_echo(connFd);
            exit(0);
        }
    }
    close(listenFd);

    return 0;
}
