#include "func.h"
#include <stdio.h>
#include <pthread.h>

void * main_t(void *);

int main(int argc,char * argv[])
{
    pthread_t tid;
    int thread_param = 5;

    if(pthread_create(&tid,NULL,main_t,(void *)&thread_param) != 0)
    {
        puts("pthread_create() error");
        return -1;
    };
    sleep(10);
    puts("end of main");
    return 0;
}

void * main_t(void * arg)
{
    int cnt = *((int *)arg);
    for(int i=0;i<cnt;i++)
    {
        sleep(1);
        puts("running thread");
    }
    return NULL;
}