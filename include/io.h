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

/** inb:
 *  reads a bytes from an IO port
 *
 *  @param port - IO port address
 *  @return     - the byte read
 */
unsigned char
inb(unsigned short port);

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

/** fb_write:
 *  writes to framebuffer, moves cursor with it
 *
 *  @param buf - buffer to write
 *  @param len - length of buffer to write
 */
void
fb_write(const char *buf, unsigned len);

#endif // IO_H
