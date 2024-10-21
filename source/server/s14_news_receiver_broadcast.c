#include "func.h"

int main(int argc,char * argv[])
{
    if(argc != 2) errors("Args Error <Port>");

    int recv_sock;
    struct sockaddr_in addr;
    int str_len;
    char buf[BUF_SIZE];

    recv_sock = socket(PF_INET,SOCK_DGRAM,0);
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(atoi(argv[1]));

    if(bind(recv_sock,(struct sockaddr *)&addr,sizeof(addr)) == ERROR)
        errors("Function returns Error");
    
    while(TRUE)
    {
        str_len = recvfrom(recv_sock,buf,BUF_SIZE-1,0,NULL,0);
        if(str_len < 0)
            break;
        buf[str_len] = 0;
        fputs(buf,stdout);
    }
    close(recv_sock);
    return 0;
}