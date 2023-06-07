; framebuffer functions

; preserve EDI, ESI, EBP, and EBX

%define FB_HIGH_BYTE_COMMAND    14         ; tells frame buffer to export bits high
%define FB_LOW_BYTE_COMMAND     15         ; tells frame buffer to export bits low
%define FB_COMMAND_PORT         0x3D4      ; port that describes data
%define FB_DATA_PORT            0x3D5      ; port that intakes data
%define VGA_ADDR                0x000B8000 ; mem addr of vga memory for frame buffer

global  outb
; send byte to an I/O port
; stack:
;       [esp + 8] the data byte
;       [esp + 4] the IO port
;       [esp    ] return address
outb:
        mov     al, [esp + 8]   ; move data to be sent into the al register
        mov     dx, [esp + 4]   ; move the address of IO port into dx
        out     dx, al           ; send the data to the IO port
        ret


global  inb
; returns a byte from given IO port
; stack:
;       [esp + 4] address of the IO port
;       [esp    ] the ret address
inb:
        mov     dx, [esp + 4]
        in      al, dx
        ret


global fb_write_cell
; write to cell of VGA mem 2bytes in size
; stack
;       - background color
;       - foreground color
;       - character
;       - cell position
;       - ret addr
fb_write_cell:
        mov     edx, VGA_ADDR           ; caller respondsibility to preserve register edx
        add     edx, [esp + 4]          ; add 1st param, call position to edx
        add     edx, [esp + 4]          ; add position again because its 2 bytes

        mov     al, byte [esp + 8]      ; mov 2nd param, character to al
        mov     ah, byte [esp + 16]     ; mov 4th param, bg color to ah
        shl     ah, 4                   ; shift to make room in the byte for the fg
        or      ah, byte [esp + 12]     ; or in the 4th param, fg color
        mov     [edx], ax               ; move the 2 bytes into edx address

        ret


global fb_move_cursor
; move cursor to position on framebuffer 80x25
; stack
;       - position for cursor
;       - ret addr
fb_move_cursor:
        ; outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND)
        push    FB_HIGH_BYTE_COMMAND            
        push    FB_COMMAND_PORT
        call    outb
        add     esp, 8
        ; outb(FB_COMMAND_PORT, ((pos >> 8) & 0x00FF))
        mov     eax, [esp + 4]
        shr     eax, 8
        and     eax, 0x00FF
        push    eax
        push    FB_DATA_PORT
        call    outb
        add     esp, 8
        ; outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
        push    FB_LOW_BYTE_COMMAND
        push    FB_COMMAND_PORT
        call    outb
        add     esp, 8
        ; outb(FB_DATA_PORT, pos & 0x00FF);
        mov     eax, [esp + 4]
        and     eax, 0x00FF
        push    eax
        push    FB_DATA_PORT
        call    outb
        add     esp, 8
        ret

