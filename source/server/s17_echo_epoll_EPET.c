#include "func.h"

#undef BUF_SIZE
#define BUF_SIZE 4
#define EPOLL_SIZE 50

void noblock(int fd)
{
    int flag = fcntl(fd,F_GETFL,0);
    fcntl(fd,F_SETFL,flag|O_NONBLOCK);
}

//设定NONBLOCK
//使得 read/write 不阻塞立即返回

int main(int argc,char * argv[])
{
    if(argc != 2) errors("Args Error <Port>");
    int serv_sock,clnt_sock;
    int str_len,epfd,event_cnt;
    socklen_t addr_size;
    char buf[BUF_SIZE];
    struct sockaddr_in serv_addr,clnt_addr;
    struct epoll_event * ep_events,event;

    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == ERROR) errors("Function socket() returns %d",ERROR);

    memset(&serv_addr,0,sizeof(serv_addr));    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == ERROR)
        errors("Function bind() returns %d",ERROR);
    
    if(listen(serv_sock,5) == ERROR)
        errors("Function listen() returns %d",ERROR);

    // int flag = fcntl(serv_sock,F_GETFL,0);
    // fcntl(serv_sock,F_SETFL,flag|O_NONBLOCK);
    noblock(serv_sock);
    
    epfd = epoll_create(EPOLL_SIZE);
    event.events = EPOLLIN;
    event.data.fd = serv_sock;
    epoll_ctl(epfd,EPOLL_CTL_ADD,serv_sock,&event);
    ep_events = (struct epoll_event *)malloc(sizeof(struct epoll_event)*EPOLL_SIZE);

    while(TRUE)
    {
        event_cnt = epoll_wait(epfd,ep_events,EPOLL_SIZE,-1);
        if(event_cnt == ERROR) errors("Function epoll_wait() returns %d",ERROR);
        puts("\nreturn epoll_wait");

        for(int i=0;i<event_cnt;i++)
        {
            if(ep_events[i].data.fd == serv_sock)
            {
                addr_size = sizeof(clnt_addr);
                clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_addr,&addr_size);
                noblock(clnt_sock);
                
                event.events = EPOLLIN|EPOLLET;
                event.data.fd = clnt_sock;
                epoll_ctl(epfd,EPOLL_CTL_ADD,clnt_sock,&event);
                success("New Client Connected %d",clnt_sock);
            }
            else
            {
                while (TRUE)
                {
                    memset(buf,0,BUF_SIZE);
                    str_len = read(ep_events[i].data.fd,buf,BUF_SIZE);
                    if (str_len == 0)
                    {
                        epoll_ctl(epfd,EPOLL_CTL_DEL,ep_events[i].data.fd,NULL);
                        close(ep_events[i].data.fd);
                        message("Client %d Disconnect",ep_events[i].data.fd);
                    }
                    else if(str_len < 0 )
                    {
                        if(errno == EAGAIN)
                            break;
                    }
                    else
                    {
                        //printf("Message From Client %d: %s\n",ep_events[i].data.fd,buf);
                        if(write(ep_events[i].data.fd,buf,str_len) == ERROR)
                            errors("Function write() returns %d",ERROR);
                    }
                }
            }
        }
    }
    close(serv_sock);
    close(epfd);
    return 0;
}