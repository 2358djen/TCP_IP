#include "func.h"
int m = 5;
void * test();

int main()
{
    printf("%d",*(int *)test());
    return 0;
}

void * test()
{
    return (void *)&m;
}