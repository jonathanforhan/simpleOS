;
; boot.S
;
global  start

%include "boot/paging.S"
%include "boot/gdt.S"
%include "boot/idt.S"

section .text
bits 32
start:
;       enable paging, see paging.S
        PAGING_INIT

;       initialize gdt64 table, see gdt.S
;       NOTE this marco puts gdt64.code in ax to be used for far jmp
        GDT_INIT

;       --- far jump to long mode ---
        push    ax
        push    long_mode_entry
        retf


section .text
bits 64
long_mode_entry:
;       main driver
        extern  kmain
        call    kmain
        hlt

section .bss
PAGING_BSS

section .rodata
GDT_RODATA
