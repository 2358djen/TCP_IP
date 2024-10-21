#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void error(char * message);

int main()
{
    int fd;
    char buf[]="Let us GO!";
    fd = open("/tmp/data.txt",O_CREAT|O_WRONLY|O_TRUNC);
    {
        // O_CREAT         必要时创建文件
        // O_TRUNC         删除全部现有数据
        // O_APPEND        维持现有数据,保存到其后面(追加)
        // O_RDONLY        只读打开
        // O_WRONLY        只写打开
        // O_RDWR          读写打开

        // 传递多个参数时, 按 "位" 或(OR) 运算组合传递
    }
    if (fd == -1)
        errors("open() error");
    printf("File Descriptor:%d\n",fd);
    if(write(fd,buf,sizeof(buf)) == -1)
        errors("write() error");
    close(fd);
    
    return 0;
}

void error(char * message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}