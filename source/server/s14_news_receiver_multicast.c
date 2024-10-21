#include "func.h"

int main(int argc,char * argv[])
{
    if(argc != 3) errors("Args Error <GroupIP> <IP>");

    int recv_sock;
    int str_len;
    char buf[BUF_SIZE];
    struct sockaddr_in addr;
    struct ip_mreq join_addr;

    recv_sock = socket(PF_INET,SOCK_DGRAM,0);
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(atoi(argv[2]));

    if(bind(recv_sock,(struct sockaddr *)&addr,sizeof(addr)) == ERROR)
        errors("Function bind() returns ERROR");
    
    join_addr.imr_multiaddr.s_addr = inet_addr(argv[1]);
    join_addr.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(recv_sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,(void *)&join_addr,sizeof(join_addr));

    while(TRUE)
    {
        str_len = recvfrom(recv_sock,buf,BUF_SIZE-1,0,NULL,0);
        if(str_len < 0) errors("Function recvfrom() returns a invalid value");
        buf[str_len] = 0;
        fputs(buf,stdout);
    }
    close(recv_sock);
    return 0;
}