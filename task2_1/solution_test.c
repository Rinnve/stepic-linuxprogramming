#include <stdio.h>
#include "solution.h"

int main() {
    const char *test1 = "test1"; // 5
    const char *test2 = "";  // 0
    int c = 0;
    printf("%i\n", stringStat(test1, 2, &c));
    printf("%i\n", c);
    printf("%i\n", stringStat(test2, 2, &c));
    printf("%i\n", c);
    return 0;
}
