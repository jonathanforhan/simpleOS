;
; idt.S
;
; void __attribute__((cdecl)) i386_idt_load(struct idt_descriptor *idt_desc);
[bits 32]
global i386_idt_load
i386_idt_load:
        mov     eax, [esp + 4]
        lidt    [eax]
        ret
