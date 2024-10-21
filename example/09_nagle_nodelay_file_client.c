#include "../include/func.h"

int main(int argc,char * argv[])
{
    if(argc != 4)
        errors("Invalid args <IP> <Port> <FilePath>");
    
    int sock,state;
    struct sockaddr_in serv_addr;
    int opt_val = 1;//Disable Nagle
    sock = socket(PF_INET,SOCK_STREAM,0);
    if(sock == -1) errors("Invalid socket");

    state = setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(void *)&opt_val,sizeof(opt_val));
    if(state == -1) errors("Invliad setsocketopt");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    state = connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if(state == -1) errors("Invalid connet");

    int file = open (argv[3],O_RDONLY);
    int read_len;
    int count = 0,counts = 0;
    char buf[BUF_SIZE];
    while(1)
    {
        memset(buf,0,BUF_SIZE);
        read_len = read(file,buf,BUF_SIZE);
        if(read_len == -1) errors("Invalid read");

        state = write(sock,buf,read_len);
        if(state == -1) errors("Invalid write");

        count += read_len;
        while(count >= BUF_SIZE)
        {
            count -= BUF_SIZE;
            counts ++;
        }
        if(read_len == 0)
        {
            printf("[ OK ] Send: %d x %d + %d (Bytes)\n",counts,BUF_SIZE,count);
            break;
        }
    }
    close(file);
    close(sock);
    return 0;
}