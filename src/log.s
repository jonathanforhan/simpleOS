; void print_string(char* dx)
;       - dx: string to print
print_string:
        push    si
        push    ax
        push    bx

        mov     si, dx          ; move arg to si for lodsb cycle
        mov     ah, 0x0e        ; BIOS print
        mov     bh, 0           ; BIOS page 0
.loop:
        lodsb                   ; load next char in si
        or      al, al          ; if al == 0 { done(); }
        jz      .done

        int     0x10            ; print BIOS int
        jmp     .loop
.done:
        pop     bx
        pop     ax
        pop     si
        ret


; void print_hex(void* dx)
;       - dx: u16/addr to print
print_hex:
        pusha

        ; BIOS print
        mov     ah, 0x0e
        mov     bh, 0
        ; Ox hex prefix
        mov     al, '0'
        int     0x10
        mov     al, 'x'
        int     0x10

        ; move 0b11110000 to al for logical & operation
        mov     al, 0xf0
        mov     cx, 0           ; count
.loop:
        ; get the 4 bits needed for hex char
        and     al, dh
        shr     al, 4

        ; convert number to hex ascii character
        cmp     al, 9
        jle     .numeric        ; skip the ascii addition if 1-9
        add     al, 7
.numeric:
        add     al, '0'

        int     0x10

        shl     dx, 4
        mov     al, 0xf0

        inc     cx
        cmp     cx, 4
        
        jne     .loop
        ; newline
        mov     al, 0x0d
        int     0x10
        mov     al, 0x0a
        int     0x10

        popa
        ret
