#include "../include/func.h"

void read_childproc(int sig)
{
    int status;
    pid_t pid = waitpid(-1,&status,WNOHANG);
    if(WIFEXITED(status))
    {
        printf("Remove Proc ID: %d\n",pid);
        printf("Child Proc Send: %d\n",WEXITSTATUS(status));
    }
}

int main(int argc,char * argv[])
{
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD,&act,0);

    pid_t pid = fork();
    if(pid == 0)
    {
        puts("Hi! I'm Child Process");
        sleep(12);
        return 12;
    }
    else
    {
        printf("Child Proc ID: %d\n",pid);
        pid = fork();
        if(pid == 0)
        {
            puts("Hi! I'm Child Process");
            sleep(8);
            exit(24);
        }
        else
        {
            printf("Child Proc ID: %d\n",pid);
            for(int i=0;i<5;i++)
            {
                puts("Wait...");
                sleep(4);
            }
        }
    }

    return 0;
}