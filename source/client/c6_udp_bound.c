#include "../../include/func.h"

int main(int argc,char * argv[])
{
    int sock;
    char m1[] = "Hi!";
    char m2[] = "I'm another UDP host!";
    char m3[] = "Nice To Meet You";

    struct sockaddr_in your_addr;
    //socklen_t your_addr_size;

    if(argc != 3)
        errors("Invliad args <IP> <Port>");
    
    sock = socket(PF_INET,SOCK_DGRAM,0);
    if(sock == -1)
        errors("Invalid sock");
    
    memset(&your_addr,0,sizeof(your_addr));
    your_addr.sin_family = AF_INET;
    your_addr.sin_addr.s_addr = inet_addr(argv[1]);
    your_addr.sin_port = htons(atoi(argv[2]));

    sendto(sock,m1,sizeof(m1),0,(struct sockaddr *)&your_addr,sizeof(your_addr));
    sendto(sock,m2,sizeof(m2),0,(struct sockaddr *)&your_addr,sizeof(your_addr));
    sendto(sock,m3,sizeof(m3),0,(struct sockaddr *)&your_addr,sizeof(your_addr));
    close(sock);
    return 0;
}