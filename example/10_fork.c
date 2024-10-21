#include "../include/func.h"


int gval = 10;
int main1(int argc,char * argv[])
{
    pid_t pid;
    int lval = 20;
    gval ++;
    lval += 5;

    pid = fork();
    if(pid == 0)
        gval += 2,lval += 2;
    else
        gval -= 2,lval -= 2;
    
    if(pid == 0)
        printf("Child Proc: [%d,%d]\n",gval,lval);
    else
        printf("Parent Proc: [%d,%d]\n",gval,lval);
    return 0;
}

int main()
{
    pid_t pid = fork();
    if(pid == 0)
    {
        sleep(10);
        pid = fork();
        if(pid == 0)
        {
            sleep(10);
            printf("Proc 2\n");
        }
        else printf("Proc 1\n");
    }
    else {printf("Proc 0\n"); sleep(30);}
}