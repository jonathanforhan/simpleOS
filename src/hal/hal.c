#include "hal.h"
#include "idt.h"

void
hal_init(void)
{
#if defined __x86_64__
    // TODO
#elif defined __i386__
    i386_idt_init();
#endif
}
