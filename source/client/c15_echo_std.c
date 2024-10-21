#include "func.h"

int main(int argc,char * argv[])
{
    if(argc != 3) errors("Args Error <IP> <Port>");
    int sock;
    char buf[BUF_SIZE] = {0};
    struct sockaddr_in serv_addr;

    sock = socket(PF_INET,SOCK_STREAM,0);
    if(sock == ERROR) errors("Function socket() returns %d",ERROR);

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == ERROR) 
        errors("Function connect() returns %d",ERROR);
    else success("Connection success!");
    
    FILE * readfp;
    FILE * writefp;

    readfp = fdopen(sock,"r");
    writefp = fdopen(sock,"w");

    while(TRUE)
    {
        fputs("Please Input Message(Q to Quit):",stdout);
        fgets(buf,BUF_SIZE,stdin);

        if((!strcmp(buf,"q\n"))||(!strcmp(buf,"Q\n")))
            break;
        
        fputs(buf,writefp);
        fflush(writefp);
        memset(buf,0,BUF_SIZE);
        fgets(buf,BUF_SIZE,readfp);
        printf("Message From Server: %s",buf);
    }

    fclose(readfp);
    fclose(writefp);
    return 0;
}