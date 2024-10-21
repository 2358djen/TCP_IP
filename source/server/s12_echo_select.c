//可以和任意回声客户端配合

#include "../../include/func.h"

int main(int argc,char * argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;
    struct timeval timeout;
    fd_set reads,copy_reads;
    socklen_t addr_size;
    int fd_max,str_len,fd_num,state;
    char buf[BUF_SIZE];
    char text[BUF_SIZE];

    if(argc != 2)
        errors("Missing Parameter: <Port>");
    
    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == ERROR) errors("Function socket() returns -1");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    state = bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if(state == ERROR) errors("Function bind() returns -1");

    state = listen(serv_sock,5);
    if(state == ERROR) errors("Function listen() return -1");
    else {success("The Server Socket Created");sprintf(text,"Server Port:%d",atoi(argv[1]));logs(text);}

    FD_ZERO(&reads);
    FD_SET(serv_sock,&reads);
    fd_max = serv_sock;

    while (TRUE)
    {
        copy_reads = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        
        fd_num = select(fd_max+1,&copy_reads,0,0,&timeout);//It's Also fine set timeout as NULL
        if(fd_num == ERROR) {printf("Function select() returns -1");break;}
        else if(fd_num == 0) continue;
        for(int i=0;i<fd_max+1;i++)
        {
            if(FD_ISSET(i,&copy_reads))
            {
                if(i == serv_sock)
                {
                    addr_size = sizeof(clnt_addr);
                    clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_addr,&addr_size);
                    if(clnt_sock == -1) errors("Function accept() returns -1");

                    FD_SET(clnt_sock,&reads);
                    if(fd_max < clnt_sock) fd_max = clnt_sock;
                    sprintf(text,"Connected Client: %d",clnt_sock);
                    success(text);
                }
                else
                {
                    str_len = read(i,buf,BUF_SIZE);
                    if(str_len == ERROR) errors("Function read() returns -1");
                    else if(str_len == 0)
                    {
                        FD_CLR(i,&reads);
                        close(i);
                        sprintf(text,"Closed Client: %d",i);
                        message(text);
                    }
                    else
                    {
                        state = write(i,buf,str_len);
                        if(state == ERROR) errors("Function write() returns -1");
                    }
                }
            }
        }
    }
    close(serv_sock);
    return 0;
}