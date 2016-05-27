/***
Разработать программу solution, которая осуществляет поиск родительского PID 
текущего процесса в файловой системе proc и выводит найденное значение на консоль.
Результат, возвращаемый функций должен быть выведен отдельной строкой (должен 
оканчиваться символом перевода строки \n) в stdio.
***/

#include <stdio.h>
#include <string.h>

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
            printf("%i\n", ppid);
            break;
        }
    }
    fclose(f);
    return 0;
}