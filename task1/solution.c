#include "solution.h"

/*
Функция возвращает значение длины строки string, 
умноженное на multiplier, и увеличивает на 1 значение, 
на которое указывает count.
*/

int stringStat(const char *string, int multiplier, int *count) {
    int len = 0;
    while (*(string++)) len++;
    (*count)++;
    return len * multiplier;
}
