//验证仅仅基于同一个文件描述符使用 fdopen 分离IO是不可行的 
#include "func.h"

int main(int argc,char * argv[])
{
    int sock;
    char buf[BUF_SIZE];
    struct sockaddr_in serv_addr;
    FILE * readfp,* writefp;
    sock = socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    readfp = fdopen(sock,"r");
    writefp = fdopen(sock,"w");

    while(TRUE)
    {
        if(fgets(buf,BUF_SIZE,readfp) == NULL)
            break;
        fputs(buf,stdout);
        fflush(stdout);
    }
    fputs("From Client: Thank You!\n",writefp);
    fflush(writefp);
    fclose(writefp);
    fclose(readfp);
    return 0;
}