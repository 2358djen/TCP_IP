#include "../include/func.h"

int main(int argc, char *argv[])
{
    fd_set reads, temps;
    int results, str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;

    FD_ZERO(&reads);
    FD_SET(0, &reads);

    // timeout.tv_sec = 5;
    // timeout.tv_usec = 5000;

    while (TRUE)
    {
        temps = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        results = select (1,&temps,0,0,&timeout);
        if(results == -1)
        {
            warning ("Invliad select");
            break;
        }
        else if (results == 0)
            message("Time Out");
        else
        {
            if(FD_ISSET(0,&temps))
            {
                memset(buf,0,BUF_SIZE);
                str_len = read (0,buf,BUF_SIZE);
                printf("Message From Console: %s",buf);
            }
        }
    }
    return 0;
}