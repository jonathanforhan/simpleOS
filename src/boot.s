; boot, using multiboot spec

%include "gdt.s"

global  loader                          ; entry symbol for elf

MAGIC_NUMBER    equ 0x1BADB002          ; define magic number
FLAGS           equ 0x0                 ; multiboot flags
CHECKSUM        equ -MAGIC_NUMBER       ; calc checksum
                                        ; MAGIC_NUMBER + CHECKSUM + FLAGS should equal 0
K_STACK_SIZE    equ 4096                ; Kernel stack size in bytes


section .text                           ; start text section
align   4                               ; code must be 4 byte aligned
        dd MAGIC_NUMBER                 ; write magic number to machine code
        dd FLAGS
        dd CHECKSUM

loader:                                 ; entry point defined in linker script
        ; point esp to start of kstack, this initializes the kernel stack
        ; to 4096 bytes
        mov     esp, kernel_stack + K_STACK_SIZE
        cli                             ; clear interupts
        lgdt    [gdt_descriptor]        ; load GDT
        mov     eax, cr0                ; switch to protected mode
        or      eax, 0x1                ; first bit of cr0, control register
        mov     cr0, eax                ; update control register

        jmp     CODE_SEG:protected_mode ; start protected mode with our new GDT
[bits 32]                               ; we've been using 32 bit instructions but they were not in
                                        ; 32-bit protected mode
protected_mode:
        mov     ax, DATA_SEG            ; in protexted mode old segments are meaningless
        mov     ds, ax
        mov     ss, ax
        mov     es, ax
        mov     fs, ax
        mov     gs, ax

        mov     ebp, 0x00090000         ; update stack pointer to free space
        mov     esp, ebp

        extern  main
        call    main

        jmp     $


section .bss                            
align   4                               ; align 4 bytes
kernel_stack:
        resb K_STACK_SIZE               ; reserve stack for the kernel
