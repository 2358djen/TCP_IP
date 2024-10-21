#include "../include/func.h"

#define TRUE 1
#define FALSE 0

int main(int argc,char * argv[])

{
    int serv_sock,clnt_sock,state;
    char message[30];
    int option,str_len;
    socklen_t optlen,clnt_addr_size;
    struct sockaddr_in serv_addr,clnt_addr;

    if(argc != 2) errors("APP <Port>");

    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == -1) errors("Invalid socket");

    optlen = sizeof(option);
    option = TRUE;
    state = setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,(void *)&option,optlen);
    if(state) errors("Invalid setsockopt");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    state = bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if(state == -1) errors("Invalid bind");

    state = listen(serv_sock,5);
    if(state == -1) errors("Invalid listen");

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept (serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_size);
    if(clnt_sock == -1) errors("Invalid accept");

    while((str_len = read(clnt_sock,message,sizeof(message))) != 0)
    {
        write(clnt_sock,message,str_len);
        write(1,message,str_len);
        memset(message,0,sizeof(message));
    }
    close(clnt_sock);
    close(serv_sock);
    return 0;
}