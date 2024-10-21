#include "../../include/func.h"

void urg_handler(int);

int acpt_sock;
int recv_sock;

int main(int argc,char * argv[])
{
    struct sockaddr_in recv_addr,serv_addr;
    int str_len,state;
    socklen_t serv_addr_size;
    struct sigaction act;
    char buf[BUF_SIZE];
    if(argc != 2) errors("Missing Paramter <Port>");

    act.sa_handler = urg_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    acpt_sock = socket(PF_INET,SOCK_STREAM,0);
    memset(&recv_addr,0,sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    recv_addr.sin_port = htons(atoi(argv[1]));

    state = bind(acpt_sock,(struct sockaddr *)&recv_addr,sizeof(recv_addr));
    if(state == ERROR) errors("Function bind() returns -1");

    state = listen(acpt_sock,5);
    if(state == ERROR) errors("Function listen() returns -1");

    serv_addr_size = sizeof(serv_addr);
    recv_sock = accept(acpt_sock,(struct sockaddr *)&serv_addr,&serv_addr_size);

    fcntl(recv_sock,F_SETOWN,getpid());
    state = sigaction(SIGURG,&act,0);

    while((str_len = recv(recv_sock,buf,sizeof(buf),0)) != 0)
    {
        if(str_len == ERROR) continue;
        buf[str_len] = 0;
        puts(buf);
    }
    close(recv_sock);
    close(acpt_sock);
    return 0;
}

void urg_handler(int signo)
{
    int str_len;
    char buf[BUF_SIZE];
    str_len = recv(recv_sock,buf,sizeof(buf)-1,MSG_OOB);
    buf[str_len] = 0;
    warning("Urgent Message: %s",buf);
}