#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

int main()
{
    int fd1,fd2,fd3;
    fd1=socket(PF_INET,SOCK_STREAM,0);
    fd2=open("/tmp/test.dat",O_CREAT,O_WRONLY,O_TRUNC);
    fd3=socket(PF_INET,SOCK_DGRAM,0);

    printf("File Descriptor1: %d\n",fd1);    
    printf("File Descriptor2: %d\n",fd2);    
    printf("File Descriptor3: %d\n",fd3);    

    close(fd1);close(fd2);close(fd3);
    return 0;
}
//描述符从3号开始顺序编号
//因为0,1,2是分配给标准I/O的描述符