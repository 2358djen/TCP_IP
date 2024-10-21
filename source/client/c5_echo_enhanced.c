#include "../../include/func.h"

int main(int argc,char * argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    if(argc != 3)
        errors("Invliad args <IP> <Port>");

    printf("Welcome To echo Message!\n");
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
    int str_len,recv_len,recv_count;
    while(1)
    {
        memset(message,0,BUF_SIZE);
        memset(recv,0,BUF_SIZE);

        fputs("Please Input Message(Q to quit): ",stdout);
        fgets(message,BUF_SIZE,stdin);

        str_len = write(sock,message,strlen(message));
        if(str_len == -1)
            errors("write error");

        if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))//即使输入Q,也传过去再退出
            break;

        recv_len = 0;recv_count = 0;
        while(recv_len < str_len)//字符串传出去再传回来需要时间,这里是为了完全接收
        {
            recv_len = read(sock,&recv[recv_count],BUF_SIZE -1);
            if(recv_len == -1)
                errors("read error");
            recv_count += recv_len;
        }

        printf("Message From Server: %s",recv);

    }
    close(sock);
    return 0;
}