/* kio.h - kernel io */
#pragma once

#ifndef NULL
#define NULL ((void*)0)
#endif

#undef EOF
#define EOF -1

void cls();
void putchar(int c);
void puts(const char *str);
void printf(const char *fmt, ...);
void sprintf(char *str, const char *fmt, ...);
