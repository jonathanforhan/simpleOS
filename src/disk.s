; void disk_load(void* bx, byte dh, u8 dl)
;       - bx: mem-addr to read data
;       - dh: number of sectors to read
;       - dl: disk to read from
disk_load:
        pusha
        push    dx

        mov     ah, 0x02        ; read-mode
        mov     al, dh          ; read dh number of sectors
        mov     cl, 0x02        ; start from sector 2 (sector 1 is boot sector)
        mov     ch, 0x00        ; cylinder 0
        mov     dh, 0x00        ; head 0

        int     0x13
        jc      disk_error

        pop     dx
        cmp     al, dh

        jne     sectors_error

        popa
        ret

disk_error:
        mov     dx, disk_error_msg
        call    error

sectors_error:
        mov     dx, sectors_error_msg
        call    error

error:
        call    print_string
        jmp     $

disk_error_msg:    db "Disk error",    0x0d, 0x0a, 0x00
sectors_error_msg: db "Sectors error", 0x0d, 0x0a, 0x00
