#include "../../include/func.h"

int main(int argc,char * argv[])
{
    int sock;
    char message[BUF_SIZE];
    struct sockaddr_in my_addr,your_addr;
    socklen_t addr_size;
    int str_len;

    if(argc != 2)
        errors("Invalid args <Port>");
    
    sock = socket(PF_INET,SOCK_DGRAM,0);
    if(sock == -1)
        errors("Invalid sock");
    
    memset(&my_addr,0,sizeof(my_addr));
    my_addr.sin_family =AF_INET;
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_port = htons(atoi(argv[1]));
    if(bind(sock,(struct sockaddr *)&my_addr,sizeof(my_addr)) == -1)
        errors("Invalid bind");
    
    for(int i=0;i<30;i++)
    {
        sleep(5);
        addr_size = sizeof(your_addr);
        str_len = recvfrom(sock,message,BUF_SIZE,0,(struct sockaddr *)&your_addr,&addr_size);
        printf("Message %d: %s\n",i+1,message);
    }
    close(sock);
    return 0;
}