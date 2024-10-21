#include "../../include/func.h"

int main(int argc,char * argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;
    socklen_t clnt_addr_size;

    if(argc != 2)
        errors("Invalid args <Port>");

    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == -1)
        errors("sock() error");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1)
        errors("bind() error");

    if(listen(serv_sock,5) == -1)
        errors("listen() error");
    
    clnt_addr_size = sizeof(clnt_addr);
    char message[BUF_SIZE];int str_len;
    for(int i=0;i<5;i++)
    {
        clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_size);
        if(clnt_sock == -1)
            errors("accept() error");
        else printf("New Connected Client %d !!\n",i+1);

        while((str_len = read(clnt_sock,message,BUF_SIZE)) != 0)
            write(clnt_sock,message,str_len);
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}