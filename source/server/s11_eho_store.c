//可与任意回声客户端配合

#include "../../include/func.h"

int main (int argc,char * argv[])

{
    if(argc != 3) error ("Invalid Args <Port> <FilePath>");

    int serv_sock,clnt_sock;
    int state,str_len;
    char buf[BUF_SIZE];
    socklen_t addr_size;
    struct sockaddr_in serv_addr,clnt_addr;
    struct sigaction act;
    pid_t pid;

    act.sa_handler = read_childproc;
    sigemptyset (&act.sa_mask);
    act.sa_flags = 0;
    sigaction (SIGCHLD,&act,0);

    serv_sock = socket (PF_INET,SOCK_STREAM,0);
    if(serv_sock == ERROR) error ("Invliad sock");

    int option = TRUE;
    socklen_t optlen = sizeof(option);
    state = setsockopt (serv_sock,SOL_SOCKET,SO_REUSEADDR,(void *)&option,optlen);
    if(state) errors("Invalid setsockopt");

    memset(&serv_addr,0,sizeof (serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl (INADDR_ANY);
    serv_addr.sin_port = htons (atoi(argv[1]));

    state = bind (serv_sock,(struct sockaddr *)&serv_addr,sizeof (serv_addr));
    if(state == ERROR) error ("Invliad bind");

    state = listen (serv_sock,5);
    if(state == ERROR) error ("Invliad listen");

    int fds[2];
    pipe (fds);
    pid = fork ();

    if (pid == 0)
    {
        char msgbuf[BUF_SIZE + 30];
        int len;

        while (TRUE)
        {
            FILE * fp = fopen(argv[2],"a+");
            memset (msgbuf,0,BUF_SIZE + 30);
            len = read(fds[0],msgbuf,BUF_SIZE + 30);
            fwrite ((void *)msgbuf,1,len,fp);
            fclose (fp);
        }
        return 0;
    }

    int count = 0;
    char msgbuf[BUF_SIZE + 30];
    while (TRUE)
    {
        addr_size = sizeof (clnt_addr);
        clnt_sock = accept (serv_sock,(struct sockaddr *)&clnt_addr,&addr_size);
        if(clnt_sock == ERROR) continue ;
        else printf ("New Client Connect %d\n",++ count);

        pid = fork ();

        if (pid == -1)
        {
            close (clnt_sock);
            continue ;
        }
        else if (pid == 0)
        {
            close (serv_sock);

            while (TRUE)
            {
                memset (buf,0,BUF_SIZE);
                memset (msgbuf,0,BUF_SIZE + 30);

                str_len = read (clnt_sock,buf,BUF_SIZE);
                if(str_len == ERROR) error ("Invliad read");

                if(!strcmp(buf,"Q\n") || !strcmp(buf,"q\n") || str_len == 0)
                {
                    printf("Client %d Quit!  ",count);
                    break;
                }else if(str_len != 0) printf("Message From Client %d: %s",count,buf);

                state = write (clnt_sock,buf,str_len);
                if(state == ERROR) error ("Invliad write");

                sprintf(msgbuf,"Message From Client %d: %s",count,buf);
                state = write (fds[1],msgbuf,str_len + 30);                
                if(state == ERROR) error ("Invliad write");
            }

            close (clnt_sock);
            return 0;
        }
        else close(clnt_sock);
    }

    close (serv_sock);
    return 0;
}