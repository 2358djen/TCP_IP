#include "../../include/func.h"

int main(int argc,char * argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    if(argc != 3)
        errors("Invliad args <IP> <Port>");

    sock = socket(PF_INET,SOCK_STREAM,0);
    if(sock == -1)
        errors("socket error");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1)
        errors("connect error");
    else puts("connected");

    char message[BUF_SIZE];
    char recv[BUF_SIZE];
    int str_len;
    while(1)
    {
        fputs("Please Input Message(Q to quit): ",stdout);
        fgets(message,BUF_SIZE,stdin);

        if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
            break;

        write(sock,message,strlen(message));
        str_len = read(sock,recv,BUF_SIZE - 1);

        message[str_len] = 0;
        printf("Message From Server: %s",recv);

    }
    close(sock);
    return 0;
}