#include "func.h"

int main(int argc,char * argv[])
{
    struct iovec vec[3];
    char buf1[BUF_SIZE] = {0,};
    char buf2[BUF_SIZE] = {0,};
    char buf3[BUF_SIZE] = {0,};
    int str_len;

    vec[0].iov_base = buf1;
    vec[0].iov_len = 5;
    vec[1].iov_base = buf2;
    vec[1].iov_len = 6;
    vec[2].iov_base = buf3;
    vec[2].iov_len = BUF_SIZE;

    str_len = readv(0,vec,3);

    printf("Read Bytes: %d\n",str_len);
    printf("First Message: %s\n",buf1);
    printf("Second Message: %s\n",buf2);
    printf("Thired Message: %s\n",buf3);

    return 0;
}