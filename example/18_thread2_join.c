#include "func.h"

void * main_t(void * arg);

int main(int argc,char * argv[])
{
    pthread_t t_id;
    int thread_param = 5;
    void * thread_ret;

    if(pthread_create(&t_id,NULL,main_t,&thread_param) != 0)
        errors("Function pthread_create() error");

    if(pthread_join(t_id,&thread_ret) != 0)
        errors("Function pthread_join() error");

    printf("Thread return message: %s\n",(char *)thread_ret);
    free(thread_ret);
    return 0;
}

void * main_t(void * arg)
{
    int cnt = *((int *)arg);
    char * msg = (char *)malloc(sizeof(char) * 50);
    strcpy(msg,"Hello I am thread!");
    for(int i=0;i<cnt;i++)
    {
        sleep(1);
        puts("running thread");
    }
    return (void *)msg;
}