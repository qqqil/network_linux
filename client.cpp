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

    int ret = connect(sock,(const struct sockaddr *)&addr,sizeof(addr));
    if(ret == -1){
        printf("connect to server failed  for  %s\n",strerror(errno));
        return -1;
    }
    return sock;
}

int main(){
    log("connect to server\n");
    int conn = getConnect();
    if(conn == -1){
        printf("connect to server failed!,%d:%s\n",errno,strerror(errno));
        exit(1);
    }
    printf("connect sock %d\n",conn);
    char buf[1024];
    char str[1024];
    bzero(buf,sizeof(buf));
    size_t len = sizeof(buf);
    int num = 0;
    char* hello ="are you ok?\n";
    int out_len =strlen(hello)+1;
    memcpy(buf,hello,strlen(hello));
    log("send data to server:\n");
    for(int i=0;i<1;i++){
        log("please input:\n");
        memcpy(buf,hello,strlen(hello));
        scanf("%s",buf);
        log(buf);
        int snd = write(conn,buf,strlen(buf));
        memset(buf,0,sizeof(buf));
        sprintf(buf,"send data to server size :%d\n",snd);
        log(buf);
    }
    log("waiting for data from server:\n");
    // while((num =recv(conn,buf,sizeof(buf),0)) >0){
    //     memset(str,0,sizeof(str));
    //     sprintf(str,"received data : %s\n",buf);
    //     log(str);
    // }
      //     memset(str,0,sizeof(str));
    //     sprintf(str,"received data : %s\n",buf);
    //     log(str);
    memset(buf,0,sizeof(buf));
    num =recv(conn,buf,sizeof(buf),0);
    printf("RCVD DATA:%s\n",buf);
    close(conn);
    return 0;
}
