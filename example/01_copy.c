#include "../include/func.h"

int main()
{
    int pre,post;
    char mail[24]="Hello Today Feel Could!";
    pre = open("/root/tcp/cache/d1",O_CREAT|O_RDWR);
    if(pre == -1)
        errors("open1() error");
    printf("1:%d\n",pre);
    if(write(pre,mail,sizeof(mail)-1) == -1)
        errors("write1() error");
    close(pre);


    char cache[24];
    pre = open("/root/tcp/cache/d1",O_RDONLY);
    if(pre == -1)
        errors("open2() error");
    printf("2:%d\n",pre);
    if(read(pre,cache,sizeof(cache)-1) == -1)
        errors("read() error");
    close(pre);

    printf("cache:%s\n",cache);

    post = open("/root/tcp/cache/d2",O_CREAT|O_RDWR|O_TRUNC);
    if(post == -1)
        errors("open3() error");
    printf("3:%d\n",post);
    if(write(post,cache,sizeof(cache)-1) == -1)
        errors("write2() error");
    close(post);
    return 0;
}

//总结:
//open()可以创建和打开包含路径的不带扩展名的文件
//同一文件连续读写操作:在每一次小操作步骤后关闭文件并重新打开再执行下一个小操作步骤
//                  或者在下一个操作步骤前使用open()重新创建文件一个描述符(文件同时具有多个活动的描述符)
//                  实验证明只用一个描述符:
                                        // 写入后读取不可
                                        // 读取后写入可以
                                        // 读取后读取可以
                                        // 写入后写入可以
//最后:严格控制传输位数,否则会出现乱码