; Master Boot Record

[org 0x7c00]
[bits 16]

; Location to load Kernel into
KERNEL_OFFSET   equ 0x1000

; BIOS sets bootdrive to dl, store in BOOT_DRIVE
mov     [BOOT_DRIVE], dl

; stack setup
mov     bp, 0x9000
mov     sp, bp

call    load_kernel
call    load_32bit

jmp     $

%include "./src/log.s"
%include "./src/disk.s"
%include "./src/gdt.s"
%include "./src/32bit.s"

[bits 16]
load_kernel:
        mov     bx, KERNEL_OFFSET       ; dest
        mov     dh, 2                   ; num sectors
        mov     dl, [BOOT_DRIVE]        ; disk
        call    disk_load
        ret

[bits 32]
BEGIN_32BIT:
        call    KERNEL_OFFSET           ; give control to kernel
        jmp     $                       ; loop is kernel fails

BOOT_DRIVE:     db 0

times   510-($-$$) db 0                 ; pad
dw      0xaa55                          ; magic
