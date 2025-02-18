#include "../../include/func.h"

int main(int argc,char * argv[])
{
    if(argc != 3)
        errors("Invliad args <IP> <Port>");
    int sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t addr_size;
    struct sockaddr_in serv_addr,from_addr;

    sock = socket(PF_INET,SOCK_DGRAM,0);
    if(sock == -1)
        errors("Invalid socket");
    
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    
    while (1)
    {
        fputs("Insert message (Q to quit): ",stdout);
        fgets(message,sizeof(message),stdin);
        if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
            break;
        
        sendto(sock,message,strlen(message),0,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

        memset(message,0,BUF_SIZE);
        addr_size = sizeof(from_addr);
        str_len = recvfrom(sock,message,BUF_SIZE,0,(struct sockaddr *)&from_addr,&addr_size);
        message[str_len] = 0;
        printf("Message From Server: %s",message);
    }
    
    close(sock);
    return 0;
}