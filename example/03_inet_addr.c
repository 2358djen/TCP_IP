#include "../include/func.h"

int main(int argc, char *argv[])
{
    char *addr1 = "1.2.3.4";
    char *addr2 = "1.2.3.256";
    unsigned long conv_addr = inet_addr(addr1);
    if (conv_addr == INADDR_NONE)
        printf("Error Occured!");
    else
        printf("NetWork Ordered Integer Addr: %#lx\n", conv_addr);

    conv_addr = inet_addr(addr2);
    if (conv_addr == INADDR_NONE)
        printf("Error Occured!");
    else
        printf("NetWork Ordered Integer Addr: %#lx\n\n", conv_addr);
    return 0;
}