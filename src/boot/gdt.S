;
; gdt.S
;

; GDT_INIT:
;       updates selectors
;       NOTE this macro places the gdt64.code ptr in ax for the
;       jmp to long mode
%macro GDT_INIT 0
        lgdt    [gdt64.pointer]
        mov     ax, gdt64.data
        mov     ss, ax
        mov     ds, ax
        mov     es, ax
        mov     ax, gdt64.code
%endmacro

%macro GDT_RODATA 0
; GDT:
;       has 3 segments
;               - NULL descriptor //
;               - code            // contains various flags
;               - data            // contains other various flags
gdt64:
        dq      0       ; NULL descriptor
.code: equ $ - gdt64
;       flags
        dq (1<<44) | (1<<47) | (1<<41) | (1<<43) | (1<<53)
.data: equ $ - gdt64
;       flags
        dq (1<<44) | (1<<47) | (1<<41)
.pointer:
        dw      .pointer - gdt64 - 1
        dq      gdt64

%endmacro
