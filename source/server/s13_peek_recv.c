#include "func.h"

int main(int argc,char * argv[])

{
    if(argc != 2) errors("Args Error <Port>");
    int acpt_sock,recv_sock;
    struct sockaddr_in acpt_addr,recv_addr;
    int str_len,state;
    socklen_t recv_addr_size;
    char buf[BUF_SIZE];

    acpt_sock = socket(PF_INET,SOCK_STREAM,0);
    memset(&acpt_addr,0,sizeof(acpt_addr));
    acpt_addr.sin_family = AF_INET;
    acpt_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    acpt_addr.sin_port = htons(atoi(argv[1]));

    state = bind(acpt_sock,(struct sockaddr *)&acpt_addr,sizeof(acpt_addr));
    if(state == ERROR) errors("Function bind() returns %d",ERROR);

    state = listen(acpt_sock,5);
    if(state == ERROR) errors("Function listen() returns %d",ERROR);

    recv_addr_size = sizeof(recv_addr);
    recv_sock = accept(acpt_sock,(struct sockaddr *)&recv_addr,&recv_addr_size);
    if(recv_sock == ERROR) errors("Function accept() returns %d",ERROR);

    while(TRUE)
    {
        str_len = recv(recv_sock,buf,sizeof(buf)-1,MSG_PEEK|MSG_DONTWAIT);
        if(str_len == ERROR) errors("Function recv() returns %d",ERROR);
        else if(str_len > 0) break;
    }
    buf[str_len] = 0;
    message("Buffering %d bytes: %s",str_len,buf);

    str_len = recv(recv_sock,buf,sizeof(buf)-1,0);
    if(str_len == ERROR) errors("Function recv() returns %d",ERROR);
    buf[str_len] = 0;
    logs("Read Again: %s",buf);
    close(recv_sock);
    close(acpt_sock);
    return 0;
}