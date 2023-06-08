; GDT
gdt_start:

gdt_null:                       ; Null descriptor defined in standard
        dd      0x0             ; dd = 4 bytes
        dd      0x0

gdt_code:                       ; code segment descriptor
        ; base = 0x0, limit = 0xfffff
        ; 1st flags: (present)1 (privlelege)00 (descriptor type)1 -> 1001b
        ; type flags: (code)1 (conforming)0 (readable)1 (accessed)0 -> 1010b
        ; 2nd flags: (granularity)1 (32-bit default)1 (64-bit seg)0 (AVL)0 -> 1100b
        dw      0xFFFF          ; limit (bits 0-15)
        dw      0x0             ; base (bits 0-15)
        db      0x0             ; base (bits 16-23)
        db      0b10011010      ; 1st falgs, type flags
        db      0b11001111      ; 2nd falgs, limit (bits 16-19)
        db      0x0             ; base (bits 24-31)

gdt_data:                       ; data segment descriptor
        ; same as code except for the type flags:
        ; type flags: (code)0 (expand down)0 (writable)1 (accessed)0 -> 0010b
        dw      0xFFFF          ; limit (bits 0-15)
        dw      0x0             ; base (bits 0-15)
        db      0x0             ; base (bits 16-23)
        db      0b10010010      ; 1st falgs, type flags
        db      0b11001111      ; 2nd falgs, limit (bits 16-19)
        db      0x0             ; base (bits 24-31)

gdt_end:

; GDT descriptor
gdt_descriptor:
        dw      gdt_end - gdt_start - 1         ; size of GDT
        dd      gdt_start                       ; gdt_start address

CODE_SEG        equ gdt_code - gdt_start
DATA_SEG        equ gdt_data - gdt_start
