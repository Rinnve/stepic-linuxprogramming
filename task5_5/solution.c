/***


***/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("Wrong argument count!\n");
        return 1;
    }
    int id1 = atoi(argv[1]), id2 = atoi(argv[2]);
    
    return 0;
}