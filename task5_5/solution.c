/***
В системе существуют 2 региона разделяемой памяти, заполненной
некоторыми числами (типа int). Каждый из регионов имеет размер 1000 байт.
Вам требуется разработать приложение, которое попарно суммирует первые 100
чисел в этих регионах и помещает суммы в новый (созданный вашим приложением)
регион памяти размером 1000 байт. Таким образом, после завершения работы
Вашего приложения в памяти должен существовать регион разделяемой памяти
размером 1000 байт, содержащий в начале 100 сумм. Перед завершением работы
приложение выводит в стандартный поток ввода-вывода ключ созданного региона,
завершающийся символом конца строки. На вход ваше приложение принимает ключи
существующих регионов памяти.

***/

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("Wrong argument count!\n");
        return 1;
    }
   
    int id1 = atoi(argv[1]), id2 = atoi(argv[2]);    
    key_t tok = ftok(argv[0], 475);
    // Allocate new shmem region of 1000 bytes.
    int newid = shmget(tok, 1000, 0666 | IPC_CREAT | IPC_EXCL);
    //printf("shmget result: %i\n", newid);
    if (newid == -1)
    {
        printf("errno: %i\n", errno);
        switch(errno)
        {
            case EACCES: printf("EACCES\n"); break;
            case EEXIST: printf("EEXIST\n"); break;
            case EINVAL: printf("EINVAL\n"); break;
            case ENFILE: printf("ENFILE\n"); break;
            case ENOENT: printf("ENOENT\n"); break;
            case ENOMEM: printf("ENOMEM\n"); break;
            case ENOSPC: printf("ENOSPC\n"); break;
            case EPERM: printf("EPERM\n"); break;
        }
        return errno;
    }
    int *arr1, *arr2, *newarr;
    arr1 = (int *) shmat(id1, NULL, SHM_RDONLY);
    arr2 = (int *) shmat(id2, NULL, SHM_RDONLY);
    newarr = (int *) shmat(newid, NULL, 0);
    
    for (int i = 0; i < 100; i++)
        newarr[i] = arr1[i] + arr2[i]; 
    
    printf("%i\n", newid);
    return 0;
}