
#include "stdio.h"
#include "fcntl.h"
#include "unistd.h"
#include "stdlib.h"

// 验证 指向同一文件的两个描述符,关闭一个对另外一个是否有影响

int main (int argc, char* argv[])
{
    if (argc <= 1)
        printf ("usage: file"), exit (-1);

    int fd1 = open (argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP);
    int fd2 = dup (fd1);
    write (fd1, "abc", 3);
    close (fd1);
    printf ("write: %ld", write (fd2, "123", 3));
    return 0;
}