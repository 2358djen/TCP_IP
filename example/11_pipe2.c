#include "../include/func.h"

int main(int argc,char * argv[])
{
    int fds[2];
    char str1[] = "Who Are You";
    char str2[] = "Thank You For Your Message";
    char buf[BUF_SIZE];

    pid_t pid;

    pipe(fds);
    // printf("[0]:%d,[1]:%d\n",fds[0],fds[1]);
    pid = fork();

    if(pid == 0)
    {
        write(fds[1],str1,sizeof(str1));
        sleep(2);
        read(fds[0],buf,BUF_SIZE);
        printf("Child Proc OutPut: %s\n",buf);
    }
    else
    {
        read(fds[0],buf,BUF_SIZE);
        printf("Parent Proc OutPut: %s\n",buf);
        write(fds[1],str2,sizeof(str2));
        sleep(3);
    }
    return 0;
}