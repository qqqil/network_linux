#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>
#include <poll.h>
#include <sys/epoll.h>

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
    printf("client id %d \n",sockfd);
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
    log("close client connection\n");
}
#define max(x,y) (x)<(y)?(y):(x)

void init_select(int listen){
   fd_set rfds; 

    struct timeval tv;
    tv.tv_sec =5;
    tv.tv_usec =0;
    
    int fd_max=0;

    fd_max = max(listen,0)+1;
    int ret = -1;
    int fds[256];
    bzero(fds,sizeof(fds));
    fds[listen]=1;
    while(1){
        FD_ZERO(&rfds);
        for(int i=0;i<256;i++){
            if(fds[i]==1){
                FD_SET(i,&rfds);
            }
        }
        ret = select(fd_max,&rfds,NULL,NULL,&tv);
        if(ret == -1){
            break;
        }
        if(ret ==0){
            continue;
        }
        printf("get data from client\n");
        for(int i=0;i<fd_max;i++){
            if(FD_ISSET(i,&rfds)){
                if(listen == i){
                    //accept
                    int client = accept(i,NULL,NULL);
                    if(client != -1){
                        fd_max = max(fd_max,client)+1;
                        fds[client]=1;
                        printf("accept connection from select: %d\n",client);
                    }else{
                        printf("accept connectioin is invalid\n");
                    }
                }else{
                    str_echo(i);
                    fds[i]=0;
                    FD_CLR(i,&rfds);
                    close(i);
                }
            }
        } 
        printf("waiting for connection..\n");
    }
    printf("exit select loop\n");
    strerror(errno);
    close(listen);
}
void init_poll(int listenFd){
    struct pollfd clients[OPEN_MAX];
    int nready=0;
    int maxi =0;
    int n=0;
    char buf[1024];
    for(int i=0;i<OPEN_MAX;i++){
        clients[i].fd = -1;
    }
    clients[0].fd = listenFd;
    clients[0].events = POLLRDNORM;
    while(1){
        nready = poll(clients,maxi+1,1*1000);
        if(nready <0){
            strerror(errno);
            exit(1);
        }
        //printf("nready = %d\n",nready);
        if(nready==0){
            continue;
        }
        if(clients[0].revents & POLLRDNORM){
            int client  = accept(clients[0].fd,NULL,NULL);
            if(client == -1){
                log("accept connection failed!\n");
                continue;
            }
            int i=0;
            for(i=1;i<OPEN_MAX;i++){
                if(clients[i].fd == -1){
                    clients[i].fd = client;
                    break;
                }
            }
            if(i==OPEN_MAX){
                log("out of max open clients!\n");
                continue;
            }
            clients[i].events = POLLRDNORM;
            if(i > maxi){
                maxi = i;
            }
            if(--nready <=0){
                continue;
            }
        } 
        for(int i=1;i<=maxi;i++){
            if(clients[i].fd <0){
               continue; 
            }
            int sock = clients[i].fd;
            if(clients[i].revents &(POLLRDNORM | POLLERR)){
                if((n = read(sock,buf,sizeof(buf)))<0){
                    if(errno == ECONNRESET){
                        close(clients[i].fd);
                        clients[i].fd = -1;
                    }else{
                        perror("unknown errors!\n");
                    }
                }else if(n ==0){
                    close(clients[i].fd);
                    clients[i].fd = -1;
                }else{
                    char str[1024];
                    bzero(str,sizeof(str));
                    log(buf);
                     sprintf(str,"recvd data: %s\n","data from server");
                     log(str);
                     write(sock,buf,n);
                      bzero(buf,sizeof(buf));//clear recieved data from the buffer 
                    close(sock);
                    clients[i].fd = -1;
                }
                if(--nready <=0){
                    break;
                }
            }
        }
    }
}
#define MAX_EVENTS 16
void init_epoll(int listenFd){
    struct epoll_event ev,events[MAX_EVENTS];
    int conn_sock,nfds,epollfd;

    epollfd = epoll_create1(EPOLL_CLOEXEC);
    if(epollfd == -1){
        perror("create epoll fd failed!\n");
        exit(1);
    }
    ev.events = EPOLLIN;
    ev.data.fd = listenFd;
    if((epoll_ctl(epollfd,EPOLL_CTL_ADD,listenFd,&ev))==-1){
        perror("add listen event to epoll failed!\n");
        exit(1);
    }
    while(1){
        nfds = epoll_wait(epollfd,events,MAX_EVENTS,-1);
        if(nfds == -1){
            perror("get event error\n");
            exit(1);
        }
        for(int i=0;i<nfds;i++){
            struct epoll_event we = events[i];
            if(we.data.fd == listenFd){
                conn_sock = accept(listenFd,NULL,NULL);
                if(conn_sock == -1){
                    continue;
                }
                struct epoll_event new_ev;
                new_ev.events = EPOLLIN |EPOLLET;
                new_ev.data.fd = conn_sock;
                if(epoll_ctl(epollfd,EPOLL_CTL_ADD,conn_sock,&new_ev)==-1){
                perror("epoll_ctl:conn_sock error\n");
                exit(1);
                }
            }else{
                char buf[512];
                bzero(buf,sizeof(buf));
               int num = read(we.data.fd,buf,sizeof(buf));
               if(num == -1){
                close(we.data.fd);
                continue;
               }
               if(num == 0){
                close(we.data.fd);
                continue;
               }
                printf("received data:%s\n",buf);
                write(conn_sock,buf,num);
                close(conn_sock);
            }
        }
    }
    close(listenFd);
}
int main(){
    int listenFd,connFd;
    pid_t childpid;
    socklen_t chilen;
    struct sockaddr_in childaddr,serverAddr;
    char str[1024];
    int ret=-1;
    bzero(str,sizeof(str));
    listenFd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&serverAddr,sizeof(serverAddr));
    
    ret = setsockopt(listenFd,SOL_SOCKET,SO_REUSEADDR,&listenFd,sizeof(listenFd));
    if(ret == -1){
        perror("set socket reuseaddr failed!\n");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(SERV_PORT);

    ret = bind(listenFd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
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
    init_epoll(listenFd);
    return 0;
}
