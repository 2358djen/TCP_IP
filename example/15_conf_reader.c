#include "func.h"

int main(int argc,char * argv[])
{
    FILE * p;
    if((p = fopen(argv[1],"r"))==NULL)
    {
        warning("Can not Access File %s",argv[1]);
        return 0;
    }
    char line[BUF_SIZE] = {0};
    char name[10] = {0};
    char option[20] = {0};
    char ip[20] = {0};
    char mask[20] = {0};
    char route[20] = {0};
    while(fgets(line,sizeof(line),p) != NULL)
    {
        rmCharacter(line,32);
        rmCharacter(line,34);
        upperConvertion(line);
        if(isNotes(line))
        {
            printf("Comments\n");
            continue;
        }
        else if(isEmptyL(line))
        {
            printf("Empty Line\n");
            continue;
        }
        else if(isContainC(line,'='))
        {
            subString(line,'=',name,option);
            printf("name=%s,option=%s\n",name,option);
        
            if(strcmp(name,"IPADDR") == 0)
                strcpy(ip,option);
            else if(strcmp(name,"NETMASK") == 0)
                strcpy(mask,option);
            else if(strcmp(name,"GATEWAY") == 0)
                strcpy(route,option);
            else warning("Unknown settings");
        }
        else warning("Unknown Options");
        
    }
    printf("\nip=%s\nmask=%s\nroute=%s",ip,mask,route);
    fclose(p);
    return 0;
}
