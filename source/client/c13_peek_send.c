#include "func.h"

int main(int argc,char * argv[])
{
    int sock;
    int state;
    struct sockaddr_in send_addr;
    if(argc != 3) errors("Args Error <IP> <Port>");

    sock = socket(PF_INET,SOCK_STREAM,0);
    memset(&send_addr,0,sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    send_addr.sin_addr.s_addr = inet_addr(argv[1]);
    send_addr.sin_port = htons(atoi(argv[2]));

    state = connect(sock,(struct sockaddr *)&send_addr,sizeof(send_addr));
    if(state == ERROR) errors("Function connect() returns %d",ERROR);

    state = write(sock,"123",strlen("123"));
    if(state == ERROR) errors("Function write() returns %d",ERROR);
    close(sock);
    return 0;
}