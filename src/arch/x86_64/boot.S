;
; boot.S
;
global start

KERNEL_STACK_SIZE equ 4096

section .text
[bits 32]
start:
        call    paging_init

        lgdt    [gdt.pointer]
        mov     ax, gdt.data
        mov     ss, ax
        mov     ds, ax
        mov     es, ax
        
        jmp     gdt.code:long_mode

[bits 64]
long_mode:
        mov     rbp, kernel_stack + KERNEL_STACK_SIZE ; point esp to start of stack
        mov     rsp, rbp
        extern  kmain
        call    kmain
        hlt


%include "arch/x86_64/gdt.S"
%include "arch/x86_64/paging.S"


section .bss
align   4
kernel_stack:
        resb    KERNEL_STACK_SIZE       ; reserve stack

