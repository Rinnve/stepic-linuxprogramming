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

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Wrong argument count!\n");
        return 1;
    }
    /* FROM TASK 6.2
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in local;
    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(atoi(argv[1]));
    local.sin_family = AF_INET;
    int result = bind(s, (struct sockaddr *) &local, sizeof(local));
    //printf("%i\n", result);
    
    const int BUF_SIZE = 5001;
    char buf[BUF_SIZE];
    while (1)
    {
        read(s, buf, BUF_SIZE);
        char *newline_pos = strchr(buf, '\n');
        if (newline_pos != NULL)
            *newline_pos = 0;
        if (strcmp(buf, "OFF") == 0) 
            break;
        printf("%s\n\n", buf);
    }
    */
    return 0;
}