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
    log("connect to server ");
    int conn = getConnect();
    if(conn == -1){
        exit(1);
    }
    char buf[1024];
    bzero(buf,sizeof(buf));
    size_t len = sizeof(buf);
    int num = 0;
    char* hello ="are you ok?";
    int out_len =strlen(hello)+1;
    memcpy(buf,hello,strlen(hello));
    write(conn,buf,out_len);
    while((num =read(conn,buf,len)) >0){
        log(buf);
        break;
    }
    log("1");
    close(conn);
    return 0;
}