#include "func.h"

int main(int argc,char * argv[])
{
    if(argc != 3) errors("Args Error! <GroupIP> <Port>");
    int send_sock;
    struct sockaddr_in multi_addr;
    int time_to_live = 64;
    char buf[BUF_SIZE];
    FILE * fp;

    send_sock = socket(PF_INET,SOCK_DGRAM,0);
    memset(&multi_addr,0,sizeof(multi_addr));
    multi_addr.sin_family = AF_INET;
    multi_addr.sin_addr.s_addr = inet_addr(argv[1]);
    multi_addr.sin_port = htons(atoi(argv[2]));

    setsockopt(send_sock,IPPROTO_IP,IP_MULTICAST_TTL,(void *)&time_to_live,sizeof(time_to_live));

    if((fp = fopen("news.txt","r")) == NULL)
        errors("Function fopen returns NULL!");

    while(!feof(fp))
    {
        fgets(buf,BUF_SIZE,fp);
        sendto(send_sock,buf,strlen(buf),0,(struct sockaddr *)&multi_addr,sizeof(multi_addr));
        sleep(2);
    }
    fclose(fp);
    close(send_sock);
    return 0;
}