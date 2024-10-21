#include "func.h"

#define EPOLL_SIZE 50

int main(int argc,char * argv[])
{
    if(argc != 2) errors("Args Error <Port>");
    int serv_sock,clnt_sock,reuseaddr = true;
    struct sockaddr_in serv_addr,clnt_addr;
    socklen_t addr_size;
    int str_len;
    char buf[BUF_SIZE];
    struct epoll_event * ep_events;
    struct epoll_event event;
    int epfd,event_cnt;

    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == ERROR) errors("Function socket() returns %d",ERROR);
    setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,(void *)&reuseaddr,sizeof(reuseaddr));

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == ERROR)
        errors("Function bind() returns %d",ERROR);
    if(listen(serv_sock,5) == ERROR)
        errors("Function listen() returns %d",ERROR);
    else success("Server socket Created");

    epfd = epoll_create(EPOLL_SIZE);
    ep_events = (struct epoll_event *)malloc(sizeof(struct epoll_event)*EPOLL_SIZE);

    event.events = EPOLLIN;
    event.data.fd = serv_sock;
    epoll_ctl(epfd,EPOLL_CTL_ADD,serv_sock,&event);

    while(TRUE)
    {
        event_cnt = epoll_wait(epfd,ep_events,EPOLL_SIZE,-1);
        if(event_cnt == ERROR) {warning("Funtion epoll_wait error");break;}

        for(int i=0;i<event_cnt;i++)
        {
            if(ep_events[i].data.fd == serv_sock)
            {
                addr_size = sizeof(clnt_addr);
                clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_sock,&addr_size);
                if(clnt_sock == ERROR) errors("Function accept() returns %d",ERROR);
                event.events = EPOLLIN;
                event.data.fd = clnt_sock;
                epoll_ctl(epfd,EPOLL_CTL_ADD,clnt_sock,&event);
                success("New Client Connected: %d",clnt_sock);
            }
            else
            {
                memset(buf,0,BUF_SIZE);
                str_len = read(ep_events[i].data.fd,buf,BUF_SIZE);
                if(str_len == ERROR) errors("Function read() returns %d",ERROR);
                else if (str_len == 0)
                {
                    epoll_ctl(epfd,EPOLL_CTL_DEL,ep_events[i].data.fd,NULL);
                    close(ep_events[i].data.fd);
                    message("Client %d Disconnect",ep_events[i].data.fd);
                }
                else
                {
                    printf("Message From Client %d: %s",ep_events[i].data.fd,buf);
                    if(write(ep_events[i].data.fd,buf,str_len) == ERROR) 
                        errors("Function write returns %d",ERROR);
                }
            }
        }
    }
    close(serv_sock);
    close(epfd);
    return 0;
}