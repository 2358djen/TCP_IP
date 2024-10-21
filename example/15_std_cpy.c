#include "func.h"

int main(int argc,char * argv[])
{
    if(argc != 3) errors("Args Error <File1> <File2>");
    FILE * fp1;
    FILE * fp2;
    int len;
    char buf[BUF_SIZE];

    fp1 = fopen(argv[1],"rb");
    fp2 = fopen(argv[2],"wb");

    do
    {
        //fgets(buf,BUF_SIZE,fp1);
        //fputs(buf,fp2);
        memset(buf,0,BUF_SIZE);
        len = fread(buf,BUF_SIZE,1,fp1);
        fwrite(buf,BUF_SIZE,1,fp2);
    }while(len > 0);

    fclose(fp1);
    fclose(fp2);
    return 0;
}