#include <stdio.h>

int Sum(int, int);

int (*p(int, int (*)(int, int)))(int, int);

int main(int argc, char *argv[])
{
    //Define Variable (Pointer)
    int (*q)(int, int);

    //(Useless Steps) Force Conversion For Constant "0"
    q = (int (*)(int,int))0;

    //Function "p" returns "Function Pointer"
    q = p(1,Sum);

    printf("Sum=%d\n", q(2, 3));
    return 0;
}
int (*p(int m, int (*x)(int, int)))(int, int)
{
    printf("Useless Variable m=%d\n", m);
    //x = Sum;
    return x;
}

int Sum(int x, int y)
{
    return x + y;
}