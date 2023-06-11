#pragma once
#include <stdint.h>

/* https://wiki.osdev.org/Interrupt_Descriptor_Table */
struct idt_entry {
    uint16_t base_low;
    uint16_t segment_selector;
    uint8_t  reserved;
    uint8_t  flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_descriptor {
    uint16_t limit;
    struct idt_entry *ptr;
} __attribute__((packed));

enum IDT_FLAGS {
    IDT_FLAG_GATE_TASK          = 0x5,
    IDT_FLAG_GATE_16BIT_INT     = 0x6,
    IDT_FLAG_GATE_16BIT_TRAP    = 0x7,
    IDT_FLAG_GATE_32BIT_INT     = 0xe,
    IDT_FLAG_GATE_32BIT_TRAP    = 0xf,

    IDT_FLAG_RING0              = (0 << 5),
    IDT_FLAG_RING1              = (1 << 5),
    IDT_FLAG_RING2              = (2 << 5),
    IDT_FLAG_RING3              = (3 << 5),

    IDT_FLAG_PRESENT            = 0x80,
};

void
i386_idt_set_gate(int interrupt, void *base, uint16_t segment_descriptor, uint8_t flags);

void
i386_idt_enable_gate(int interrupt);

void
i386_idt_disable_gate(int interrupt);

void
i386_idt_init(void);

