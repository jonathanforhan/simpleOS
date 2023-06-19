#include <kassert.h>
#include <kio.h>

void
__assert (const char *msg, const char *file, int line)
{
    printf("assertion %s failed in %s on line %d\n", msg, file, line);
    while (1); // hang
}
