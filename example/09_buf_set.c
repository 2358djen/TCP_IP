#include "../include/func.h"

int main(int argc,char * argv[])

{
    int sock;
    int snd_buf = 1024 * 8;
    int rcv_buf = 1024 * 16;
    int state;
    socklen_t len;

    sock = socket(PF_INET,SOCK_STREAM,0);

    //set socket buffer
    state = setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void *)&rcv_buf,sizeof(rcv_buf));
    if(state) errors("Invalid setsockopt");

    state = setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void *)&snd_buf,sizeof(snd_buf));
    if(state) errors("Invalid setsockopt");

    //get socket buffer
    len = sizeof(snd_buf);
    state = getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void *)&snd_buf,&len);
    if(state) errors("Invalid setsockopt");

    len = sizeof(rcv_buf);
    state = getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void *)&rcv_buf,&len);
    if(state) errors("Invalid setsockopt");

    printf("Input Buffer Size: %d\n",rcv_buf);
    printf("Output Buffer Size: %d\n",snd_buf);
    return 0;
}