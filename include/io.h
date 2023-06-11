#pragma once

void __attribute__((cdecl))
outb(unsigned short port, unsigned char value);

unsigned char __attribute__((cdecl))
inb(unsigned short port);
