#include "../../include/func.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
        errors("Invalid args: [APP] <IP> <Port> <FilePath>");
    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        errors("Invalid socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        errors("Invalid connect");
    else
        success("Connected");

    long filesize = file_size2(argv[3]);

    int file, read_len;
    int bytes = 0;
    int gib = 0, mib = 0, kib = 0;
    long count = 0;
    int integer = 0;
    float ratio;
    char buf[BUF_SIZE];
    file = open(argv[3], O_RDONLY);
    if (file == -1)
        errors("Invalid open file");
    while (1)
    {
        memset(buf, 0, BUF_SIZE);
        read_len = read(file, buf, BUF_SIZE);
        if (read_len == -1)
            errors("Invalid read");
        if (write(sock, buf, read_len) == -1)
            errors("Invalid write");

        count += read_len;
        ratio = ((float)count / (float)(filesize / 100));
        procbar_f(ratio, TRUE);

        bytes += read_len;
        while (bytes >= 1024)
        {
            bytes -= 1024;
            kib++;
        }

        while (kib >= 1024)
        {
            kib -= 1024;
            mib++;
        }
        while (mib >= 1024)
        {
            mib -= 1024;
            gib++;
        }

        if (read_len == 0)
        {
            if ((int)ratio < 100)
            {
                procbar_f(ratio, FALSE);
                printf("[ STOPTED ] Send: %d GiB + %d (MiB) + %d (KiB) + %d (Bytes)\n", gib, mib, kib, bytes);
            }
            else
            {
                char *mess;
                sprintf(mess, "Send: %d GiB + %d (MiB) + %d (KiB) + %d (Bytes)\n", gib, mib, kib, bytes);
                message(mess);
            }
            break;
        }
    }

    close(file);
    close(sock);

    return 0;
}