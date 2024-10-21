#include "func.h"

int main(int argc,char * argv[])
{
    FILE * fp;
    char buf[BUF_SIZE]={0};
    int fd = open(argv[1],O_CREAT|O_RDWR,0);
    if(fd == ERROR) errors("Can not Open File");

    fp = fdopen(fd,"w");
    //转化后不能关闭 fd,否则 fp 仍然无法写入
    //close(fd);
    fseek(fp,0,SEEK_END);
    fputs("NetWork",fp);
    fseek(fp,0,SEEK_SET);
    fclose(fp);
    read(fd,buf,BUF_SIZE);
    puts(buf);
    close(fd);
    return 0;
}