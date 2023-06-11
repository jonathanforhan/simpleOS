#include <stdio.h>
#include <stdint.h>
#include "io.h"

static const unsigned SCREEN_WIDTH  = 80;
static const unsigned SCREEN_HEIGHT = 25;
static const uint8_t  DEFAULT_COLOR = 0x7;

static uint8_t* screen_buffer = (uint8_t*)0xB8000;
static unsigned screen_x = 0, screen_y = 0;

void
putchr(int x, int y, char c)
{
    screen_buffer[2 * (y * SCREEN_WIDTH + x)] = c;
}

void
putcolor(int x, int y, uint8_t color)
{
    screen_buffer[2 * (y * SCREEN_WIDTH + x) + 1] = color;
}

char
getchr(int x, int y)
{
    return screen_buffer[2 * (y * SCREEN_WIDTH + x)];
}

uint8_t
getcolor(int x, int y)
{
    return screen_buffer[2 * (y * SCREEN_WIDTH + x) + 1];
}

void
setcursor(int x, int y)
{
    int pos = y * SCREEN_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void
clear_screen(void)
{
    unsigned x, y;

    for (y = 0; y < SCREEN_HEIGHT; ++y)
        for (x = 0; x < SCREEN_WIDTH; ++x) {
            putchr(x, y, '\0');
            putcolor(x, y, DEFAULT_COLOR);
        }

    screen_x = 0;
    screen_y = 0;
    setcursor(screen_x, screen_y);
}

void
scrollback(int lines)
{
    unsigned x, y;

    for (y = lines; y < SCREEN_HEIGHT; y++) {
        for (x = 0; x < SCREEN_WIDTH; x++)
        {
            putchr(x, y - lines, getchr(x, y));
            putcolor(x, y - lines, getcolor(x, y));
        }
    }

    for (y = SCREEN_HEIGHT - lines; y < SCREEN_HEIGHT; ++y) {
        for (x = 0; x < SCREEN_WIDTH; ++x) {
            putchr(x, y, '\0');
            putcolor(x, y, DEFAULT_COLOR);
        }
    }

    screen_y -= lines;
}

void
putc(char c)
{
    unsigned i;

    switch (c) {
        case '\n':
            screen_x = 0;
            screen_y++;
            break;
    
        case '\t':
            for (i = 0; i < 4 - (screen_x % 4); i++)
                putc(' ');
            break;

        case '\r':
            screen_x = 0;
            break;

        default:
            putchr(screen_x, screen_y, c);
            screen_x++;
            break;
    }

    if (screen_x >= SCREEN_WIDTH) {
        screen_y++;
        screen_x = 0;
    }

    if (screen_y >= SCREEN_HEIGHT)
        scrollback(1);

    setcursor(screen_x, screen_y);
}

void
puts(const char* str)
{
    while(*str)
    {
        putc(*str);
        str++;
    }
}

const char hex_chars[] = "0123456789abcdef";

void
printf_unsigned(unsigned long long number, int radix)
{
    char buffer[32];
    int pos = 0;
    unsigned long long rem;
}

void
printf_signed(long long number, int radix)
{
    if (number < 0) {
        putc('-');
        printf_unsigned(-number, radix);
    }
    else printf_unsigned(number, radix);
}

#define PRINTF_STATE_NORMAL         0
#define PRINTF_STATE_LENGTH         1
#define PRINTF_STATE_LENGTH_SHORT   2
#define PRINTF_STATE_LENGTH_LONG    3
#define PRINTF_STATE_SPEC           4

#define PRINTF_LENGTH_DEFAULT       0
#define PRINTF_LENGTH_SHORT_SHORT   1
#define PRINTF_LENGTH_SHORT         2
#define PRINTF_LENGTH_LONG          3
#define PRINTF_LENGTH_LONG_LONG     4

void
printf(const char* fmt, ...)
{
    // FIXME TODO
}

void
print_buffer(const char* msg, const void* buffer, uint32_t count)
{
    uint16_t i;
    const uint8_t* u8_buffer = (const uint8_t*)buffer;

    puts(msg);
    for (i = 0; i < count; i++)
    {
        putc(hex_chars[u8_buffer[i] >> 4]);
        putc(hex_chars[u8_buffer[i] & 0xF]);
    }
    puts("\n");
}
