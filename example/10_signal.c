#include "../include/func.h"

void timeout(int sig)
{
    if(sig == SIGALRM)
        puts("Time Out!");
    alarm(2);
}

void keycontrol(int sig)
{
    if(sig == SIGINT)
        puts("Ctrl + C Pressed!");
}

int main(int argc,char * argv[])
{
    signal(SIGALRM,timeout);
    signal(SIGINT,keycontrol);
    alarm(2);

    for(int i=0;i<3;i++)
    {
        puts("Wait...");
        sleep(100);//发生信号时将唤醒由于调用sleep函数而进入阻塞状态的进程
    }
    return 0;
}