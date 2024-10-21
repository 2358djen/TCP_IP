#include "../../include/func.h"

int main(int argc,char * argv[])
{
    if(argc != 2)
        errors("Invalid args <Port>");
    int serv_sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t clnt_addr_size;
    struct sockaddr_in serv_addr,clnt_addr;

    serv_sock = socket(PF_INET,SOCK_DGRAM,0);
    if(serv_sock == -1)
        errors("Invalid socket");
    
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1)
        errors("Invalid bind");
    
    while (1)
    {
        memset(message,0,BUF_SIZE);
        clnt_addr_size = sizeof(clnt_addr);        
        str_len = recvfrom(serv_sock,message,BUF_SIZE,0,(struct sockaddr *)&clnt_addr,&clnt_addr_size);
        printf("Message From Client: %s",message);
        sendto(serv_sock,message,str_len,0,(struct sockaddr *)&clnt_addr,clnt_addr_size);
    }
    
    close(serv_sock);
    return 0;
}