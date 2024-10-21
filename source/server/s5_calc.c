#include "../../include/func.h"

int calc(int ,int [],char,int *);

int main(int argc,char * argv[])
{
    if(argc != 2)errors("Invalid args <Port>");

    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;
    socklen_t clnt_addr_size;

    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == -1)errors("Invalid socket!");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serv_addr.sin_port = htons(atoi(argv[1]));
    if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1)
        errors("Invalid bind");
    
    if(listen(serv_sock,5) == -1)
        errors("Invalid listen");
    
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_size);
    if(clnt_sock == -1)
        errors("Invalid accept");

    int count;
    if(read(clnt_sock,&count,sizeof(count)) == -1)
        errors("Invalid read");
    if(count <= 1)errors("Invalid 'counts'");
    int num[count];

    if(read(clnt_sock,num,sizeof(num)) == -1)
        errors("Invalid read");

    char op;
    if(read(clnt_sock,&op,sizeof(op)) == -1)
        errors("Invalid read");

    printf("%d\n",count);
    for(int i=0;i<count;i++)
    {
        printf("%d ",num[i]);
    }
    printf("\n%c",op);

    int result[2];
    result[0] = calc(count,num,op,&result[1]);

    if(write(clnt_sock,(int *)result,sizeof(result)) == -1)
        errors("Invalid write");

    close(clnt_sock);
    close(serv_sock);
    return 0;
}

int calc(int count,int num[],char op,int * flag)
{
    int res=num[0],i=0;
    *flag = 0;
    switch (op)
    {
    case '+':
    {
        for(i=0;i<count;i++)
            res += num[i];
    }
        break;
    
    case '-':
    {
        for(i=0;i<count;i++)
            res -= num[i];
    }
        break;

    case '*':
    {
        for(i=0;i<count;i++)
            res *= num[i];
    }
        break;

    case '/':
    {
        if(num[0] == 0)
        {
            *flag = 0;
            return 0;
        }

        for(i=1;i<count;i++)
        {
            if(num[i] == 0)
            {
                *flag = 1;
                return 1;
            }
            res /= num[i];
        }
    }
        break;

    default:
    {
        *flag = 2;
        return 2;
    }
        break;
    }
    return res;
}