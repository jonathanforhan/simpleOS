#include <stdint.h>
#include "hal/hal.h"

int
kmain(void)
{
    hal_init();

    short *fb = (short *) 0x000b8000;
    *(fb + 0) = 0x0230 + sizeof(void *); // H

    return 0;
}
