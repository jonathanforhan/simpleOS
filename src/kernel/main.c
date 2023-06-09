/*  kernel.c - the C part of the kernel */
#include <kio.h>
#include <klib.h>
#include <multiboot2.h>

/* Check if MAGIC is valid and print the Multiboot information structure
   pointed by ADDR. */
void
kmain (unsigned long magic, unsigned long addr) {
    cls();
    printf("MAGIC_NUMBER: 0x%x\n", magic);
    printf("INFO ADDR: 0x%x\n\n", addr);
}

/*  Copyright (C) 1999, 2010  Free Software Foundation, Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
