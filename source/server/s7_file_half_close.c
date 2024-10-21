#include "../../include/func.h"

int main(int argc,char * argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;
    socklen_t clnt_addr_size;
    char buf[BUF_SIZE];
    int read_len;
    int status;
    FILE * fp;

    if(argc != 3)
        errors("Invalid args <Port> <FilePath>");
    
    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == -1)
        errors("Invalid socket");
    
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    status = bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if(status == -1)
        errors("Invalid bind");

    status = listen(serv_sock,5);
    if(status == -1)
        errors("Invalid listen");
    
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_size);
    if(clnt_sock == -1)
        errors("Invalid accept");
    
    fp = fopen(argv[2],"rb");
    while (1)
    {
        read_len = fread((void *)buf,1,BUF_SIZE,fp);
        status = write(clnt_sock,buf,BUF_SIZE);
        if(status == -1)
            errors("Invalid write");
        if(read_len < BUF_SIZE)
            break;
    }
    status = shutdown(clnt_sock,SHUT_WR);
    if(status == -1)
        errors("Invalid shutdown");
    memset(&buf,0,BUF_SIZE);
    status = read (clnt_sock,buf,BUF_SIZE);
    if(status == -1)
        errors("Invalid read");
    
    printf("Message From Client: %s\n",buf);

    fclose(fp);
    close(clnt_sock);
    close(serv_sock);
    
    return 0;
}