#include "hal/hal.h"
#include "arch/i386/idt.h"

void
hal_init(void)
{
    // GDT get implemented before far jump to kernel
    // no need to do it here

#if defined __x86_64__
    // TODO

#elif defined __i386__
    i386_idt_init();

#endif
}
