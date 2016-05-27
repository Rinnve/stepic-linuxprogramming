/***
Разработать программу solution, которая при запуске себя "демонизирует"
и остается в  памяти. Перед закрытием стандартного потока вывода stdout
унаследованного от родителя, программа должна вывести в него Pid процесса-демона.
***/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int pid = fork();
    if (pid)
    {
        // Parent
        printf("%i\n", pid);
        return 0;
    } else
    {
        // Child
        chdir("/");
        //int child_pid = 
        setsid();
        //printf("daemon: %i\n", child_pid);
        while (1)
        {
            // Do nothing 'till the end of time
        }
    }
}