#include "func.h"

int main(int argc,char * argv[])
{
    if(argc != 3) errors("Args Error <File1> <File2>");
    int fd1,fd2;
    int len,state;
    char buf[BUF_SIZE];

    fd1 = open(argv[1],O_RDONLY);
    fd2 = open(argv[2],O_TRUNC|O_CREAT|O_WRONLY,0);

    if(fd1 == ERROR)
        errors("File %s Open Failed!",argv[1]);
    else if(fd2 == ERROR)
        errors("File %s Open Failed",argv[2]);

    do
    {
        memset(buf,0,BUF_SIZE);
        len = read(fd1,buf,BUF_SIZE);
        state = write(fd2,buf,len);
        if(state == ERROR) errors("Function write() returns %d",ERROR);
    } while (len > 0);
    
    close(fd1);
    close(fd2);
    return 0;
}