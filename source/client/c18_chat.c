#include "func.h"
#ifdef BUF_SIZE
#undef BUF_SIZE
#define BUF_SIZE 100
#define NAME_SIZE 20

void * send_msg(void * arg);
void * recv_msg(void * arg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

int main(int argc,char * argv[])
{
    if(argc != 4)errors("Args Error <IP> <Port> <Name>");
    int sock;
    struct sockaddr_in serv_addr;
    pthread_t send_thread,recv_thread;
    void * thread_return;
    sprintf(name,"[ %s ]",argv[3]);
    sock = socket(PF_INET,SOCK_STREAM,0);

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == ERROR)
        errors("Function connect() returns %d",ERROR);

    pthread_create(&send_thread,NULL,send_msg,(void *)&sock);
    pthread_create(&recv_thread,NULL,recv_msg,(void *)&sock);
    pthread_join(send_thread,&thread_return);
    pthread_join(recv_thread,&thread_return);
    close(sock);
    return 0;
}

void * send_msg(void * arg)
{
    int sock = *((int *)arg);
    char name_msg[NAME_SIZE+BUF_SIZE];

    while(TRUE)
    {
        memset(msg,0,BUF_SIZE);
        memset(name_msg,0,NAME_SIZE+BUF_SIZE);
        fgets(msg,BUF_SIZE,stdin);
        if(!strcmp(msg,"q\n") || !strcmp(msg,"Q\n"))
        {
            close(sock);
            exit(0);
        }
        sprintf(name_msg,"%s %s",name,msg);
        if(write(sock,name_msg,strlen(name_msg)) == ERROR)
            errors("Function write error");
    }
    return NULL;
}

void * recv_msg(void * arg)
{
    int sock = *((int *)arg);
    char name_msg[NAME_SIZE+BUF_SIZE];
    int str_len;
    while(TRUE)
    {
        memset(name_msg,0,NAME_SIZE+BUF_SIZE);
        str_len = read(sock,name_msg,NAME_SIZE+BUF_SIZE-1);
        if(str_len == ERROR) return (void *)ERROR;
        fputs(name_msg,stdout);
    }
    return NULL;
}

#endif