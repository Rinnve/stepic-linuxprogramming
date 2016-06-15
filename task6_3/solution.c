/***
Разработайте TCP сервер, предназначенный для сортировки символов в строке.
Сервер получает на вход строки, оканчивающиеся символом '\0', сортирует в них
символы в порядке убывания ASCII-кодов и отсылает обратно на клиент,
в виде строки заканчивающейся '\0'. Завершение работы сервера происходит
после получения строки, содержащей только 'OFF'. 

При старте сервер получает на вход номер порта в качестве параметра
командной строки. bind производится на адресе 127.0.0.1
***/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int  chrcomp(const void *p1, const void *p2)
{
    return *(char *) p2 - *(char *) p1; 
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Wrong argument count!\n");
        return 1;
    }
    
    struct sockaddr_in local;
    int servsock = socket(AF_INET, SOCK_STREAM, 0);    
    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(atoi(argv[1]));
    local.sin_family = AF_INET;
    bind(servsock, (struct sockaddr *) &local, sizeof(local));    
    listen(servsock, 5);    
    int clientsock = accept(servsock, NULL, NULL);
    
    const int BUF_SIZE = 5001;
    char buf[BUF_SIZE];
    while (1)
    {
        // We should only get zero-terminated string
        int string_len = read(clientsock, buf, BUF_SIZE) - 1;
        buf[string_len+1] = 0;     
        if (strcmp(buf, "OFF") == 0) 
            break;
        qsort(buf, string_len, sizeof(char), chrcomp);
        write(clientsock, buf, string_len + 1);                
    }
    
    return 0;
}