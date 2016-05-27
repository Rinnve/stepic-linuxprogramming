/***
Разработать программу solution, которая по заданному pid, осуществляет поиск пути 
в дереве процессов до процесса с идентификатором 1 (init). Для каждого найденного 
процесса печатается в отдельной строке его идентификатор.
***/

#include <stdio.h>
#include <string.h>

int getpid()
{
    char buf[255];
    FILE *f = fopen("/proc/self/status", "r");    
    int pid;
    while (fgets(buf, sizeof(buf), f))
    {
        char tag[255];
        pid = -1;
        sscanf(buf, "%s\t%i", tag, &pid);
        if (strcmp(tag, "Pid:") == 0)        
            break;
    }
    fclose(f);
    return pid;
}

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

int main()
{
    int pid, ppid;
    pid = getpid();
    printf("%i\n", pid);
    ppid = getppid(pid);
    while (ppid != 1)
    {
        printf("%i\n", ppid);
        ppid = getppid(ppid);
    }
    printf("1\n");
    return 0;
}
