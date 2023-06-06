#include "../include/io.h"

#define FB_HIGH_BYTE_COMMAND  14    // tells frame buffer to export bits high
#define FB_LOW_BYTE_COMMAND   15    // tells frame buffer to export bits low
#define FB_COMMAND_PORT       0x3d4 // port that describes data
#define FB_DATA_PORT          0x3d5 // port that intakes data

static char *const fb = (char *) 0x000B8000;

void
fb_write_cell(unsigned i, char c, unsigned char fg, unsigned char bg)
{
    i *= 2;
    fb[i] = c;
    fb[i + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);
}

void
fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00ff));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x0ff);
}

void
print(const char *s, unsigned len)
{
    unsigned i;

    for (i = 0; i < len; ++i) {
        fb_write_cell(i, s[i], 7, 0);
        fb_move_cursor(i+1);
    }
}
