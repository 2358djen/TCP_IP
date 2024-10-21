#include "../../include/func.h"

int main(int argc,char * argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char buf[BUF_SIZE];
    int read_len;
    int status;
    FILE * fp;

    if(argc != 4)
        errors("Invliad args <IP> <Port> <FilePath>");
    
    sock = socket(PF_INET,SOCK_STREAM,0);
    if(sock == -1)
        errors("Invalid socket");
    
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    status = connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if(status == -1)
        errors("Invalid connect");
    
    fp = fopen(argv[3],"wb");

    while((read_len = read(sock,buf,BUF_SIZE)) !=0)
        fwrite((void *)buf,1,read_len,fp);
    
    puts("File recevied");
    status = write(sock,"Thank You!",11);
    if (status == -1)
        errors("Invalid write");
    
    fclose(fp);
    close(sock);
    return 0;
}