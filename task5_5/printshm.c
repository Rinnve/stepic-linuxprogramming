#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char** argv)
{            
    if (argc != 2)
    {
        printf("Usage: printshm key");
    }
    int key = atoi(argv[1]);
    int id = shmget(key, 1000, 0666);
    int *arr = (int *) shmat(id, NULL, 0);
    
    for (int i = 0; i < 100; i++)
        printf("%i ", arr[i]);
    return 0;
}