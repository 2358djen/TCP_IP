#include "../../include/func.h"

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;
    int idx = 0;
    int str_len =0,write_len = 0;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
    char message[11] = "HelloWorld\0";
    if (argc != 2)
    {
        printf("Usage:%s <Port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        errors("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        errors("bind() error");
    if (listen(serv_sock, 5) == -1)
        errors("listen() error");

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1)
        errors("accept() error");

    while(write_len = write(clnt_sock,&message[idx++],1))
    {
        if(write_len == -1)
        {
            printf("idx=%d",idx);
            errors("write() Error");
        }
        str_len += write_len;
        if(str_len >= 11)break;
    }
    printf("Function Write Count:%d\n",str_len);
    //write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}