#include "../../include/func.h"

int main(int argc,char * argv[])
{
    int sock;
    int state;
    struct sockaddr_in recv_addr;
    if(argc != 3) errors("Missing Paramters <IP> <Port>");

    sock = socket(PF_INET,SOCK_STREAM,0);
    memset(&recv_addr,0,sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    recv_addr.sin_port = htons(atoi(argv[2]));

    state = connect(sock,(struct sockaddr *)&recv_addr,sizeof(recv_addr));
    if(state == ERROR) errors("Function connect() returns -1");

    state = write(sock,"123",strlen("123"));
    if(state == ERROR) errors("Function write() returns -1");
    sleep(3);
    state = send(sock,"4",strlen("4"),MSG_OOB);
    if(state == ERROR) errors("Function send() returns -1");
    sleep(3);

    state = write(sock,"567",strlen("567"));
    if(state == ERROR) errors("Function write() returns -1");
    sleep(3);
    state = send(sock,"890",strlen("890"),MSG_OOB);
    if(state == ERROR) errors("Function send() returns -1");

    close(sock);
    return 0;
}