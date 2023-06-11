;
; gdt.S
;
; DOCS:
; - https://wiki.osdev.org/GDT_Tutorial
; - https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
;
gdt:
;       first 8 bytes is the NULL descriptor
        dd      0
        dd      0

.code:  equ $ - gdt
;       base = 0x0, limit = 0xfffff,
;       access byte = 0x9a, flags = 0xc
        dw      0xffff  ; limit (bits 0x-15)
        dw      0       ; base (bits 0-15)
        db      0       ; base (bits 16-23)
        db      0x9a    ; access byte (see os-dev.pdf page 36 or os-dev wiki)
        db      0xcf    ; flags, limit (bits 16-19) -> 0xc0 | 0xf
        db      0       ; base (bits 24-31)

.data:  equ $ - gdt
;       base = 0x0, limit = 0xfffff,
;       access byte = 0x92, flags = 0xc
        dw      0xffff  ; limit (bits 0x-15)
        dw      0       ; base (bits 0-15)
        db      0       ; base (bits 16-23)
        db      0x92    ; access byte
        db      0xcf    ; flags, limit (bits 16-19) -> 0xc0 | 0xf
        db      0       ; base (bits 24-31)

.pointer:
        dw      .pointer - gdt - 1
        dd      gdt
