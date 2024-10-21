#include "func.h"

int main(int argc,char * argv[])
{
    FILE * fp;
    // int fd = open(argv[1],O_CREAT|O_WRONLY,0);
    // if(fd == ERROR) errors("Can not Open File");
    // fp = fdopen(fd,"a");
    // fputs("Hahaha",fp);
    // printf("First File NO:%d\n",fd);
    // printf("Second File NO:%d\n",fileno(fp));

    fp = fopen(argv[1],"r");
    if(fp == NULL) errors("Can not access file");

    int fd = fileno(fp);
    char buf[BUF_SIZE]={'a','b',99,100,101,102};

    write(fd,buf,5);
    // read(fd,buf,BUF_SIZE);
    // fgets(buf,BUF_SIZE,fp);
    // puts(buf);

    return 0;
}