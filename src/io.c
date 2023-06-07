#include "../include/io.h"

#define FB_GREY  7
#define FB_BLACK 0

void
fb_write(const char *buf, unsigned len)
{
    int i;
    for (i = 0; i < len; ++i) {
        fb_write_cell(i, buf[i], FB_GREY, FB_BLACK);
    }
    fb_move_cursor(i);
}
