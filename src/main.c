#include "../include/io.h"

int
main(void)
{
    char s[] = "Hello, World!";
    print(s, sizeof(s) - 1);
    return 0;
}
