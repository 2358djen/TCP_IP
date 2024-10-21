#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUF_SIZE 100

void error(char * message);

int main()
{
    
    int fd;
    char buf[BUF_SIZE];
    fd = open("/tmp/data.txt",O_RDONLY);
    if(fd == -1)
        errors("open() error");
    printf("File Discriptor:%d\n",fd);
    if(read(fd,buf,sizeof(buf))==-1)
        errors("read() error");
    printf("file data:%s",buf);
    return 0;
}

void error(char * message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}