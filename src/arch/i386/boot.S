;
; boot.S
;
global start

KERNEL_STACK_SIZE equ 4096

section .text
[bits 32]
start:
        cli

        lgdt    [gdt.pointer]
        mov     ax, gdt.data
        mov     ss, ax
        mov     ds, ax
        mov     es, ax
        
        jmp     gdt.code:protected_mode

protected_mode:
        mov     ebp, kernel_stack + KERNEL_STACK_SIZE ; point esp to start of stack
        mov     esp, ebp
        extern  kmain
        call    kmain
        hlt


%include "arch/i386/gdt.S"


section .bss
align   4
kernel_stack:
        resb    KERNEL_STACK_SIZE       ; reserve stack
