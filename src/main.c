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

int
main(void)
{
    scroll_buffer();
    scroll_buffer();
    scroll_buffer();
    scroll_buffer();
    scroll_buffer();
    fb_write("Welcome to Jonny's Operating System", 36);
    scroll_buffer();
    fb_write("Hello, World!", 13);
}
