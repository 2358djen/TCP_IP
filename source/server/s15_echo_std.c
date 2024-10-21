#include "func.h"

int main(const int argc,const char * argv[])
{
    if(argc != 2) errors("Args Error <Port>");
    int serv_sock,clnt_sock;
    char buf[BUF_SIZE] = {0};
    struct sockaddr_in serv_addr,clnt_addr;
    socklen_t clnt_addr_size;
    FILE * readfp, * writefp;
    fd_set reads,cpreads;
    int fd_max,fd_num;

    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == ERROR) errors("Function socket() returns %d",ERROR);

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == ERROR) 
        errors("Function bind() returns %d",ERROR);
    
    if(listen(serv_sock,5) ==ERROR)
        errors("Function listen() returns %d",ERROR);
    else success("Server socket Created!");

    FD_ZERO(&reads);
    FD_SET(serv_sock,&reads);
    fd_max = serv_sock;

    while (TRUE)
    {
        cpreads = reads;
        fd_num = select(fd_max+1,&cpreads,0,0,NULL);
        if(fd_num <= 0) {warning("Function select() Error");continue;}
        else
        {
            for(int i=0;i<=fd_max;i++)
            {
                if(FD_ISSET(i,&cpreads))
                {
                    if(i == serv_sock)
                    {
                        clnt_addr_size = sizeof(clnt_addr);
                        clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_size);
                        if(clnt_sock == ERROR) errors("Funtion accept() returns %d",ERROR);
                        else FD_SET(clnt_sock,&reads);
                        if(clnt_sock >= fd_max)fd_max = clnt_sock;
                        success("New Client Connected: %d",clnt_sock);
                    }
                    else
                    {
                        readfp = fdopen(i,"r");
                        writefp = fdopen(i,"w");
                        memset(buf,0,BUF_SIZE);
                        fgets(buf,BUF_SIZE,readfp);
                        if(strlen(buf) == 0)
                        {
                            message("Client %d Disconnected!",i);
                            FD_CLR(i,&reads);
                            fclose(readfp);
                            fclose(writefp);
                        }
                        else 
                        {
                            printf("Message From Client %d: %s",i,buf);
                            fputs(buf,writefp);
                            fflush(writefp);
                        }
                    }
                }
                else continue;
            }
        }
    }
    
}