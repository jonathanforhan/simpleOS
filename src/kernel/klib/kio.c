#include <kio.h>
#include <karg.h>
#include <kdef.h>

#define COMMAND_PORT        0x3D4
#define DATA_PORT           0x3D5
#define HIGH_BYTE_COMMAND   14
#define LOW_BYTE_COMMAND    15

#define COLUMNS             80
#define ROWS                25
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

static void
_scroll_stdout()
{
    int i;
    for (i = 0; i < COLUMNS * ROWS; i++)
        ((short *)video)[i] = ((short *)video)[i + COLUMNS];
}

static void
_putstring(const char *str)
{
    const char *ptr;
    for (ptr = str; *ptr != '\0'; ptr++)
        putchar(*ptr);
}

static const char *
_itoa(int val, char *str, int base)
{
    // ensure 2 <= base <= 16 (kassert depends on kio.c and therefore there is no assert here)
    if (val == 0)
        str[0] = '0';

    int mod = 1, places = 1;
    int n = val;
    char c;

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
        c = '0' + (n % base);
        if (c > '9')
            c += 7; // 58 -> 65 ; or 'A'
        str[places] = c;
        places--;
    }

    return str;
}

void
cls()
{
    int i;
    for (i = 0; i < COLUMNS * ROWS; ++i) {
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
        if (ypos + 1 <= ROWS) {
            ypos++;
        } else {
            _scroll_stdout();
        }
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
            case 'b':
                _itoa(va_arg(ap, int), buffer, 2);
                _putstring(buffer);
                break;
            case 'c':
                putchar(va_arg(ap, int));
                break;
            case 'd':
            case 'i':
                _itoa(va_arg(ap, int), buffer, 10);
                _putstring(buffer);
                break;
            // case 'f': TODO FIXME
                break;
            case 'o':
                _itoa(va_arg(ap, int), buffer, 8);
                _putstring(buffer);
                break;
            case 's':
                _putstring(va_arg(ap, char *));
                break;
            case 'x':
                _itoa(va_arg(ap, int), buffer, 16);
                _putstring(buffer);
                break;
            case 'p':
                _itoa(va_arg(ap, int), buffer, 16);
                _putstring("0x");
                _putstring(buffer);
                break;
            case '%':
                putchar('%');
                break;
            default:
                printf("Invalid string format\n");
                goto err;
        }
    }

    err:
    va_end(ap);
}
