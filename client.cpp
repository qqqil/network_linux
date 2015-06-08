#include "constant.h"

void log(char* str){
    printf("%s\n",str);
}
int getConnect(){
    struct sockaddr_in addr;
    int sock;
    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock == -1){
        log("sock error");
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERV_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int client = connect(sock,(const struct sockaddr *)&addr,sizeof(addr));
    return client;
}

int main(){
    log("connect to server\n");
    int conn = getConnect();
    if(conn == -1){
        log("connect to server failed!\n");
        strerror(errno);
        exit(1);
    }
    char buf[1024];
    char str[1024];
    bzero(buf,sizeof(buf));
    size_t len = sizeof(buf);
    int num = 0;
    char* hello ="are you ok?\n";
    int out_len =strlen(hello)+1;
    memcpy(buf,hello,strlen(hello));
    log("send data to server:\n");
    int snd = write(conn,buf,strlen(hello));
    memset(buf,0,sizeof(buf));
    sprintf(buf,"send data to server size :%d\n",snd);
    log(buf);
    log("waiting for data from server:\n");
    while((num =read(conn,buf,len)) >0){
        memset(str,0,sizeof(str));
        sprintf(str,"received data : %s\n",buf);
        log(str);
    }
    log("1");
    close(conn);
    return 0;
}
