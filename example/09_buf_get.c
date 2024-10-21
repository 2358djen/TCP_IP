#include "../include/func.h"

int main(int argc,char * argv[])

{
    int sock;
    int snd_buf,rcv_buf,state;
    socklen_t len;

    sock = socket(PF_INET,SOCK_STREAM,0);
    
    len = sizeof(snd_buf);
    state = getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void *)&snd_buf,&len);
    if(state)
        errors("Invalid getsockopt");
    
    len = sizeof(rcv_buf);
    state = getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void *)&rcv_buf,&len);
    if(state)
        errors("Invalid getsockopt");
    
    printf("Input Buffer Size: %d\n",rcv_buf);
    printf("Output Buffer Size: %d\n",snd_buf);
    return 0;
}