#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <dlfcn.h>


int main(int argc, char *argv[]) {
    const char* libName = argv[1];
    const char* funcName = argv[2];
    const int number = atoi(argv[3]);
    
    void *hdl = dlopen(libName, RTLD_LAZY);
    if (NULL == hdl) return -1;
    
    int (*func) (int) = (int (*)(int)) dlsym(hdl, funcName);
    if (NULL == func) return -1;
    
    printf("%i\n", func(number));
    return 0;    
}