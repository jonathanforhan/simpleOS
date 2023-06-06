; framebuffer functions

global  outb

; send byte to an I/O port
; stack:
;       [esp + 8] the data byte
;       [esp + 4] the IO port
;       [esp    ] return address
outb:
        mov     al, [esp + 8]   ; move data to be sent into the al register
        mov     dx, [esp + 4]   ; move the address of IO port into dx
        out     dx, al          ; send the data to the IO port
        ret
