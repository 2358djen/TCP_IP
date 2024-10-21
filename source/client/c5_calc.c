#include "../../include/func.h"

int main(int argc,char * argv[])
{
    if(argc != 3)
        errors("Invliad args <IP> <Port>");

    int count;
    char op;
    printf("Welcome To Cloud Calc!\nPlease Input The Number Of Numbers: ");
    scanf("%d",&count);
    if(count <= 1)errors("[ Error ] Invalid Number!");
    int num[count];
    printf("Please Input Each Numbers In Order: ");
    for(int i=0;i<count;i++)
        scanf("%d",&num[i]);
    getchar();
    printf("Input Operation Symbol: ");
    scanf("%c",&op);
    // if(op != '+' && op != '-' && op != '*' && op != '/')
    //     errors("[ Error ] Invalid Operation Symbol!");

    //Init: test data 
    //num[0] = 1;num[1] = 2;num[2] = 3;op = '+';

    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(PF_INET,SOCK_STREAM,0);
    if(sock == -1)errors("[ Error ] Invalid Socket!");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1)
        errors("[ Error ] Invalid connect!");

    if(write(sock,(int *)&count,sizeof(count)) == -1)
        errors("[ Error ] Invalid write!");

    if(write(sock,(int *)num,sizeof(num)) == -1)
        errors("[ Error ] Invalid write!");
    
    if(write(sock,&op,sizeof(op)) == -1)
        errors("[ Error ] Invalid write!");

    int result[2] = {0,0};
    if(read(sock,(int *)result,sizeof(result)) == -1)
        errors("[ Error ] Invalid read");
    
    //printf("%d, %d",result[0],result[1]);
    if(result[1] == 1)
        errors("[ Error ] Invalid Divisor");
    else if (result[1] == 2)
        errors("[ Error ] Invalid Operation Symbol");
    else if(result[1] == 0)
        printf("The Result Is: %d",result[0]);
    close(sock);
    return 0;
}