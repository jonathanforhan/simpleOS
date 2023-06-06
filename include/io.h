#ifndef IO_H
#define IO_H

/** outb:
 *  sends the given data to given IO port. See io.s
 *
 *  @param port - IO port to send data to
 *  @param data - given data to send to IO port
 */
void
outb(unsigned short port, unsigned char data);

/** fb_write_cell:
 *  write a character to framebuffer with given foreground and background color at position i
 *
 *  @param i  - position on framebuffer to write
 *  @param c  - the character
 *  @param fg - the foreground color
 *  @param bg - the background color
 */
void
fb_write_cell(unsigned i, char c, unsigned char fg, unsigned char bg);

/** fb_move_cursor:
 *  move cursor to given position
 *
 *  @param pos - position on framebuffer to move cursor
 */
void
fb_move_cursor(unsigned short pos);

/** print:
 *  prints to framebuffer, moves cursor with it
 *
 *  @param s   - string to print
 *  @param len - length of string to print
 */
void
print(const char *s, unsigned len);

#endif // IO_H
