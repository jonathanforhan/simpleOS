#include "arch/i386/idt.h"
#include "util.h"

static struct idt_entry idt[256];

static struct idt_descriptor idt_desc = { sizeof(idt) - 1, idt };

void
__attribute__((cdecl)) i386_idt_load(struct idt_descriptor *idt_desc);

void
i386_idt_set_gate(int interrupt, void *base, uint16_t segment_descriptor, uint8_t flags)
{
    idt[interrupt].base_low = ((uint32_t)base) & 0xffff;
    idt[interrupt].segment_selector = segment_descriptor;
    idt[interrupt].reserved = 0;
    idt[interrupt].flags = flags;
    idt[interrupt].base_high = ((uint32_t)base >> 16) & 0xffff;
}

void
i386_idt_enable_gate(int interrupt)
{
    FLAG_SET(idt[interrupt].flags, IDT_FLAG_PRESENT);
}

void
i386_idt_disable_gate(int interrupt)
{
    FLAG_UNSET(idt[interrupt].flags, IDT_FLAG_PRESENT);
}

void
i386_idt_init(void)
{
    i386_idt_load(&idt_desc);
}

