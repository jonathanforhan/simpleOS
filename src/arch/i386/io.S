;
; io.h
;

; void __attribute__((cdecl))
; outb(unsigned short port, unsigned char value);
global outb
[bits 32]
outb:
    mov dx, [esp + 4]
    mov al, [esp + 8]
    out dx, al
    ret

; unsigned char __attribute__((cdecl))
; inb(unsigned short port);
global inb
[bits 32]
inb:
    mov dx, [esp + 4]
    xor eax, eax
    in al, dx
    ret
