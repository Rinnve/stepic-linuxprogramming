/***
Разработайте утилиту командной строки, принимающую на вход имя хоста
и печатающую в стандартный поток вывода список IP-адресов, ассоциированных
с данным именем.
***/

#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Wrong argument count!\n");
        return 1;
    }
    struct hostent *h;
    h = gethostbyname(argv[1]);
    return 0;
}