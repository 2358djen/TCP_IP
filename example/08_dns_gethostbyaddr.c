#include "../include/func.h"

int main(int argc,char * argv[])
{
    struct hostent * host;
    struct sockaddr_in addr;
    if(argc != 2)
        errors("Invalid args <addr>");
    
    memset(&addr,0,sizeof(addr));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    host = gethostbyaddr((char *)&addr.sin_addr,4,AF_INET);
    if(host == NULL)
        errors("Can NOT find Host");
        
    printf("Official Name: %s\n",host -> h_name);

    for(int i=0;host -> h_aliases[i];i++)//last one is NULL
        printf("Aliases %d: %s\n",i+1,host -> h_aliases[i]);

    if(host -> h_addrtype == AF_INET)
        printf("AddrType: AF_INET\n");
    else if(host -> h_addrtype == AF_INET6)
        printf("AddrType: AF_INET6\n");
    else    
        printf("Unknown AddrType!\n");

    for(int i=0;host -> h_addr_list[i];i++)
        printf("IP addr %d: %s\n",i+1,inet_ntoa(*(struct in_addr *)host -> h_addr_list[i]));
    return 0;
}