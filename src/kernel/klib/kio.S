/* kio.S - kernel low level io */

        .globl outb
outb:
        xor     %al, %al
        movb    8(%esp), %al
        mov     4(%esp), %dx
        out     %al, %dx
        ret
