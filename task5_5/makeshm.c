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
        printf("Usage: makeshm some_integer");
    }
    key_t tok = ftok(argv[0], atoi(argv[1]));
    // Allocate new shmem region of 1000 bytes.
    int newid = shmget(tok, 1000, 0666 | IPC_CREAT | IPC_EXCL);
    printf("shmget result: %i\n", newid);
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
        
    int *newarr = (int *) shmat(newid, NULL, 0);
    
    for (int i = 0; i < 100; i++)
        newarr[i] = i; 
    
    printf("ID: %i\n", newid);
    printf("KEY: %i\n", tok);
    return 0;
}