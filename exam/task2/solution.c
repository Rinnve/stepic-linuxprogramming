/***
Разработать программу solution, которая осуществляет поиск PID процесса,
являющегося родителем родителя текущего процесса (то есть являющегося "дедушкой")
в файловой системе proc и выводит найденное значение на консоль.
Результат, должен быть выведен отдельной строкой (должен оканчиваться
символом перевода строки \n) в stdout.
***/

#include <stdio.h>
#include <string.h>

int getppid(int pid)
{
    char fname[255];
    sprintf(fname, "/proc/%i/status", pid);
    char buf[255];
    FILE *f = fopen(fname, "r");    
    int ppid;
    while (fgets(buf, sizeof(buf), f))
    {
        char tag[255];
        ppid = -1;
        sscanf(buf, "%s\t%i", tag, &ppid);
        if (strcmp(tag, "PPid:") == 0)        
            break;
    }
    fclose(f);
    return ppid; 
}

int main(int argc, char** argv) 
{
    char buf[255];
    FILE *f = fopen("/proc/self/status", "r");    
    while (fgets(buf, sizeof(buf), f))
    {
        char tag[255];
        int ppid = -1;
        sscanf(buf, "%s\t%i", tag, &ppid);
        if (strcmp(tag, "PPid:") == 0)
        {
            int grandparent_ppid = getppid(ppid);
            printf("%i\n", grandparent_ppid);
            break;
        }
    }
    fclose(f);
    return 0;
}