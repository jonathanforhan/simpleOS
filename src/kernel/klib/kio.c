#include <kio.h>
#include <karg.h>
#include <kdef.h>

#define COMMAND_PORT        0x3D4
#define DATA_PORT           0x3D5
#define HIGH_BYTE_COMMAND   14
#define LOW_BYTE_COMMAND    15

#define COLUMNS             80
#define LINES               24
#define ATTRIBUTE           7
#define VIDEO               0xB8000

static int xpos = 0;
static int ypos = 0;

static volatile unsigned char *video = (unsigned char *)VIDEO;

extern void outb(unsigned short port, unsigned char data);

static void
_correct_cursor()
{
    unsigned short pos = xpos + ypos * COLUMNS;

    outb(COMMAND_PORT, HIGH_BYTE_COMMAND);
    outb(DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(COMMAND_PORT, LOW_BYTE_COMMAND);
    outb(DATA_PORT,    pos & 0x00FF);
}

static const char *
_itoa(int val, char *str, int base)
{
    // ensure base != 1 (kassert depends on kio.c and therefore there is no assert here)
    if (val == 0)
        str[0] = '0';

    int mod = 1, places = 1;
    int n = val;

    if (val < 0) {
        places++;
        mod = -1;
        str[0] = '-';
    }

    while (n /= base)
        places++;

    str[places] = 0;
    places--;

    for (n = val * mod; n != 0; n /= base) {
        str[places] = '0' + (n % base);
        places--;
    }

    return str;
}

static void
_putstring(const char *str)
{
    const char *ptr;
    for (ptr = str; *ptr != '\0'; ptr++)
        putchar(*ptr);
}

void
cls()
{
    int i;
    for (i = 0; i < COLUMNS * LINES; ++i) {
        *(video + i * 2) = 0;
        *(video + i * 2 + 1) = ATTRIBUTE;
    }
    xpos = 0, ypos = 0;
}

void
putchar (int c)
{
    if (c == '\n' || c == '\r') {
    newline:
        xpos = 0;
        ypos++;
        if (ypos >= LINES)
            ypos = 0;

        _correct_cursor();
        return;
    }

    *(video + (xpos + ypos * COLUMNS) * 2) = c & 0xFF;
    *(video + (xpos + ypos * COLUMNS) * 2 + 1) = ATTRIBUTE;

    xpos++;
    if (xpos >= COLUMNS)
        goto newline;

    _correct_cursor();
}

void
puts(const char *str)
{
    _putstring(str);
    putchar('\n');
}

void
printf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    const char *ptr;
    char buffer[33];

    for (ptr = fmt; *ptr != '\0'; ptr++) {
        if (*ptr != '%') {
            putchar(*ptr);
            continue;
        }
        ptr++;
        switch (*ptr) {
            case 's':
                _putstring(va_arg(ap, char *));
                break;
            case 'd':
                _itoa(va_arg(ap, int), buffer, 10);
                _putstring(buffer);
                break;
            case '%':
                putchar('%');
                break;
            default:
                printf("Invalid string format\n");
                return;
        }
    }

    va_end(ap);
}
