#include "../../include/func.h"

int main(int argc,char * argv[])
{
    int sock;
    char message[BUF_SIZE];
    struct sockaddr_in addr;

    if(argc != 3)
        errors("Invliad args <IP> <Port>");

    sock = socket(PF_INET,SOCK_DGRAM,0);
    if(sock == -1)
        errors("Invalid sock");
    
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));


    //Function "connect()" Means Sign IP and Port To Sock
    //Not Means Connet To UDP HOST
    if(connect(sock,(struct sockaddr *)&addr,sizeof(addr)) == -1)
        errors("Invalid Sign");                          

     while (1)
    {
        fputs("Insert message (Q to quit): ",stdout);
        fgets(message,sizeof(message),stdin);
        if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
            break;
        write(sock,message,strlen(message));
        memset(message,0,BUF_SIZE);
        read(sock,message,BUF_SIZE);
        printf("Message From Server: %s",message);
    }
    
    close(sock);
    return 0;
}