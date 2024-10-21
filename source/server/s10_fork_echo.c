#include "../../include/func.h"

int main(int argc,char * argv[])

{
    if(argc != 2)
        errors("Invalid args <Port>");
    int serv_sock,clnt_sock;
    socklen_t addr_size;
    struct sockaddr_in serv_addr,clnt_addr;
    struct sigaction act;
    char buf[BUF_SIZE];
    int str_len,state;
    pid_t pid;

    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    state = sigaction(SIGCHLD,&act,0);

    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == ERROR) errors("Invalid socket");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    state = bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if(state == ERROR) errors("Invalid bind");

    state = listen(serv_sock,5);
    if(state == ERROR) errors("Invalid listen");

    int count = 0;
    while(TRUE)
    {
        addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_addr,&addr_size);
        if(clnt_sock == ERROR) continue;
        else printf("New Host Connected %d\n",++ count);

        pid = fork();
        if(pid == -1)
        {
            close(clnt_sock);
            continue;
        }
        else if (pid == 0)
        {
            close(serv_sock);
            while (TRUE)
            {
                str_len = read(clnt_sock,buf,BUF_SIZE);
                if(str_len == -1) errors("Invalid read");

                if(!strcmp(buf,"Q\n") || !strcmp(buf,"q\n"))
                {
                    printf("Client %d Quit!  ",count);
                    break;
                }
                else printf("Message From Client %d: %s",count,buf);

                if(write(clnt_sock,buf,str_len) == -1)
                    errors("write error");
                memset(buf,0,BUF_SIZE);
            }
            close(clnt_sock);
            return 0;
            
        }
        else close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}