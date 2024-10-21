#include "func.h"

void * rd(void * arg);
void * ac(void * arg);

static sem_t sem_one;
static sem_t sem_two;
static int num;

int main(int argc,char * argv[])
{
    pthread_t id_t1,id_t2;
    sem_init(&sem_one,0,0);
    sem_init(&sem_two,0,1);

    pthread_create(&id_t1,NULL,rd,NULL);
    pthread_create(&id_t2,NULL,ac,NULL);

    pthread_join(id_t1,NULL);
    pthread_join(id_t2,NULL);

    sem_destroy(&sem_one);
    sem_destroy(&sem_two);
    return 0;
}

void * rd(void * arg)
{
    for(int i=0;i<5;i++)
    {
        fputs("Input num: ",stdout);
        sem_wait(&sem_two);
        scanf("%d",&num);
        sem_post(&sem_one);
    }
    return NULL;
}

void * ac(void * arg)
{
    int sum = 0;
    for(int i=0;i<5;i++)
    {
        sem_wait(&sem_one);
        sum += num;
        sem_post(&sem_two);
    }
    printf("Result: %d\n",sum);
    return NULL;
}