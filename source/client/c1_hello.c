#include "../../include/func.h"

int main(int argc,char * argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;

    if(argc != 3)
    {
        printf("Usage:%s <IP> <Port>",argv[0]);
        exit(1);
    }
    sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock == -1)
        errors("socket() error");
    
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    //inet_aton(argv[1],&serv_addr.sin_addr);
    serv_addr.sin_port=htons(atoi(argv[2]));

    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
        errors("connect() error");
    str_len=read(sock,message,sizeof(message)-1);
    if(str_len == -1)
        errors("read() error");
    printf("Message From Server:%s",message);
    close(sock);
    return 0;
}