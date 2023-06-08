#include "../include/io.h"

#define VGA_BUFFER 80 * 24
#define VGA_MEM_ADDR (short *) 0x000B8000

void
scroll_buffer(void)
{
    unsigned i, n;
    short *const fb = VGA_MEM_ADDR;
    for (i = 0; i <= VGA_BUFFER; ++i) {
        n = VGA_BUFFER - i + 80;
        fb[n] = fb[n - 80];
    }
    for (i = 0; i < 80; ++i) {
        fb_write_cell(i, '\0', 7, 0);
    }
}

void
write_number(int n)
{
    char c;
    int len = 0, cpy = n;

    if (n == 0) {
        fb_write_cell(0, '0', 7, 0);
        fb_move_cursor(1);
        return;
    }

    while (cpy > 0) {
        len++;
        cpy /= 10;
    }

    fb_move_cursor(len);

    while (n > 0) {
        c = '0' + (n % 10);
        fb_write_cell((--len), c, 7, 0);
        n /= 10;
    }
}

int
main(void)
{
    int i;

    scroll_buffer();
    scroll_buffer();
    scroll_buffer();
    scroll_buffer();
    scroll_buffer();
    fb_write("Welcome to Jonny's Operating System", 36);
    scroll_buffer();

    for (i = 0; i < 10; ++i) {
        scroll_buffer();
        write_number(i);
    }
}
