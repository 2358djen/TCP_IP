#include "../include/func.h"

int main(int argc,char * argv[])
{
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("Host Ordered Port:  %#x\n",host_port);
    printf("Net Ordered Port:   %#x\n",net_port);
    printf("Host Ordered Addr:  %#lx\n",host_addr);
    printf("Net Ordered Addr:   %#lx\n",net_addr);
    return 0;
}