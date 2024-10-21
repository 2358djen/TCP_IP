#include "func.h"

int main(int argc,char * argv[])
{
    if(argc != 3) errors("Args Error <Broadcast IP> <Port>");
    int send_sock;
    int so_brd = 1;
    struct sockaddr_in broad_addr;
    FILE * fp;
    char buf[BUF_SIZE];

    send_sock = socket(PF_INET,SOCK_DGRAM,0);
    memset(&broad_addr,0,sizeof(broad_addr));
    broad_addr.sin_family = AF_INET;
    broad_addr.sin_addr.s_addr = inet_addr(argv[1]);
    broad_addr.sin_port = htons(atoi(argv[2]));

    setsockopt(send_sock,SOL_SOCKET,SO_BROADCAST,(void *)&so_brd,sizeof(so_brd));
    if((fp = fopen("news.txt","r")) == NULL)
        errors("Function fopen() returns NULL");
    
    while(!feof(fp))
    {
        fgets(buf,BUF_SIZE,fp);
        sendto(send_sock,buf,strlen(buf),0,(struct sockaddr *)&broad_addr,sizeof(broad_addr));
        sleep(2);
    }
    close(send_sock);
    return 0;
}