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
#include <time.h>

void printerr()
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
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("Wrong argument count!\n");
        return 1;
    }
    srand(time(NULL));
    key_t tok = ftok(argv[0], rand());
    // Allocate new shmem region of 1000 bytes.
    int newid = shmget(tok, 1000, 0666 | IPC_CREAT);
    //printf("shmget result: %i\n", newid);
    if (newid == -1)
    {
        printerr();   
        return errno;
    }
    
    key_t key1 = atoi(argv[1]), key2 = atoi(argv[2]);
    int id1 = shmget(key1, 1000, 0666);
    int id2 = shmget(key2, 1000, 0666);
    
    int *arr1, *arr2, *newarr;
    arr1 = (int *) shmat(id1, NULL, SHM_RDONLY);
    arr2 = (int *) shmat(id2, NULL, SHM_RDONLY);
    newarr = (int *) shmat(newid, NULL, 0);
    
    for (int i = 0; i < 100; i++)
        newarr[i] = arr1[i] + arr2[i]; 
    
    printf("%i\n", tok);
    return 0;
}