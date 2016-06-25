/***
Разработать программу solution, которая по заданному pid,
осуществляет поиск пути в дереве процессов до процесса с
идентификатором 1 (init) и определяет длину этого пути
(число процессов, включая заданный и init).
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

int main(int argc, char *argv[])
{
    if (argc != 2)
        return -1;    
    int pid, ppid;
    sscanf(argv[1], "%i", &pid);
    //printf("%i\n", pid);
    ppid = getppid(pid);
    int len = 1;
    while (ppid != 1)
    {
        len++;
        ppid = getppid(ppid);
    }
    printf("%i\n", len+1);
    return 0;
}
