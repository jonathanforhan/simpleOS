; boot, using multiboot spec

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

loader:                                 ; entry point definde in linker script
        ; point esp to start of kstack, this initializes the kernel stack
        ; to 4096 bytes
        mov     esp, kernel_stack + K_STACK_SIZE
        extern  main
        call    main
.loop:
        jmp     $


section .bss                            
align   4                               ; align 4 bytes
kernel_stack:
        resb K_STACK_SIZE               ; reserve stack for the kernel
