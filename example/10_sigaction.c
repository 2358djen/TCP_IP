#include "../include/func.h"
//#include <bits/sigaction.h>

void timeout(int sig)
{
    if(sig == SIGALRM)
        puts("Time Out!");
    alarm(2);
}

int main(int argc,char * argv[])
{
    struct sigaction act;
    act.sa_handler = timeout;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM,&act,0);
    // SIGREG(SIGALRM,timeout);
    alarm(2);

    for(int i=0;i<3;i++)
    {
        puts("Wait...");
        sleep(100);
    }
    return 0;
}