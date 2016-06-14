/***
Разработайте утилиту командной строки, принимающую на вход имя хоста
и печатающую в стандартный поток вывода список IP-адресов, ассоциированных
с данным именем.
***/

#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Wrong argument count!\n");
        return 1;
    }
    struct hostent *h;
    h = gethostbyname(argv[1]);
    
    int i = 0;
    while (h->h_addr_list[i] != NULL)
    {   struct in_addr *addr = (struct in_addr *) h->h_addr_list[i];
        printf("%s\n", inet_ntoa(*addr));
        i++;
    }
    
    return 0;
}