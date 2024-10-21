#include "../../include/func.h"

int main(int argc,char *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int idx = 0;
    int str_len = 0,read_len = 0;
    if (argc != 3)
    {
        printf("Usage: %s <IP> <Port>\n",argv[0]);
        exit(1);
    }
    sock = socket(PF_INET,SOCK_STREAM,0);
    if(sock == -1)errors("socket() error");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));

    if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1)
        errors("connect() error");
    
    sleep(3);

    while (read_len = read(sock,&message[idx++],1))
    {
        if(read_len == -1)
            errors("read() error");
        str_len += read_len;    
    }
    printf("Message From Server:%s\n",message);
    printf("Function read call count %d \n",str_len);
    close(sock);
    return 0;
}