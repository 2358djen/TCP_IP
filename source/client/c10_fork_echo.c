#include "../../include/func.h"

void read_routine(int ,char *);
void write_routine(int ,char *);

int main(int argc,char * argv[])
{
    if(argc != 3) errors("Invliad args <IP> <Port>");
    pid_t pid;
    int sock;
    struct sockaddr_in serv_addr;
    char buf[BUF_SIZE];

    sock = socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    int state;
    state = connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if(state == ERROR) errors("Invalid connect");

    pid = fork();
    if(pid == 0)
        write_routine(sock,buf);
    else
        read_routine(sock,buf);
    
    close(sock);
    return 0;
}

void read_routine(int sock,char * buf)
{
    while(TRUE)
    {
        int str_len = read(sock,buf,BUF_SIZE);
        if(str_len == 0) return;
        printf("Message From Server: %s",buf);
        memset(buf,0,BUF_SIZE);
    }
}

void write_routine(int sock,char * buf)
{
    while(TRUE)
    {
        fgets(buf,BUF_SIZE,stdin);
        int str_len = write(sock,buf,BUF_SIZE);
        if(!strcmp(buf,"q\n") || !strcmp(buf,"Q\n"))
        {
            shutdown(sock,SHUT_WR);
            return;
        }
        memset(buf,0,BUF_SIZE);
    }
}