//验证仅仅基于同一个文件描述符使用 fdopen 分离IO是不可行的 

#include "func.h"

int main(int argc,char * argv[])
{
    int serv_sock,clnt_sock;
    FILE * readfp,* writefp;
    struct sockaddr_in serv_addr,clnt_addr;
    char buf[BUF_SIZE] = {0,};
    socklen_t clnt_addr_size;

    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    listen(serv_sock,5);
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_size);

    readfp = fdopen(clnt_sock,"r");
    writefp = fdopen(clnt_sock,"w");

    fputs("Hi Client!\n",writefp);
    fputs("I Love All Of The World\n",writefp);
    fputs("You Are Awesome!\n",writefp);
    fflush(writefp);

    fclose(writefp);
    fgets(buf,BUF_SIZE,readfp);
    fputs(buf,stdout);
    fclose(readfp);
    return 0;
}