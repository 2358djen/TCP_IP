#include "../../include/func.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
        errors("Invalid args: [APP] <Port> <FilePath>");
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_len;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        errors("Invalid socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        errors("Invalid bind");

    if (listen(serv_sock, 5) == -1)
        errors("Invalid listen");

    clnt_addr_len = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_len);
    if (clnt_sock == -1)
        errors("Invalid accept");

    int file, recv_len;
    int bytes = 0;
    int gib = 0, mib = 0, kib = 0;
    char buf[BUF_SIZE];
    file = open(argv[2], O_CREAT | O_RDWR | O_TRUNC);
    if (file == -1)
        errors("Invalid file path");

    while (1)
    {
        memset(buf, 0, BUF_SIZE);
        recv_len = read(clnt_sock, buf, BUF_SIZE);
        if (recv_len == -1)
            errors("Invalid read");
        if (write(file, buf, recv_len) == -1)
            errors("Invalid write");

        bytes += recv_len;
        while(bytes >= 1024)
        {
            bytes -= 1024;
            kib ++;
        }

        while(kib >= 1024)
        {
            kib -= 1024;
            mib ++;
        }
        while(mib >= 1024)
        {
            mib -= 1024;
            gib ++;
        }

        if(recv_len == 0)
        {
            printf("[ OK ] Recevied: %d GiB + %d (MiB) + %d (KiB) + %d (Bytes)\n",gib,mib,kib,bytes);
            break;
        }
    }

    close(file);
    close(clnt_sock);
    close(serv_sock);
    return 0;
}