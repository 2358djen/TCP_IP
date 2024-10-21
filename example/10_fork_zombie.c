#include "../include/func.h"

int main(int argc, char *argv[])
{
    pid_t pid = fork();

    if (pid == 0)
        puts("Hello, I'am Child Process!");
    else
    {
        printf("Child Process: %d\n",pid);
        sleep(30);
    }

    if(pid == 0)
        puts("End Child Process");
    else
        puts("End Parent Process");
    return 0;
}