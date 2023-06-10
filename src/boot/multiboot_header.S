;
; multiboot_header.S
;
MAGIC   equ 0xe85250d6
ARCH    equ 0x0

section         .multiboot_header
header_start:
        dd      MAGIC                           ; magic number
        dd      ARCH                            ; protected mode code (architecture)
        dd      header_end - header_start       ; header length
        ; checksum
        dd      0x100000000 - (MAGIC + ARCH + (header_end - header_start))
        ; end tag
        dw      0       ; type
        dw      0       ; flags
        dd      8       ; size
header_end:
