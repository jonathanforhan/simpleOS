# $@ = target file
# $< = first dependency
# $^ = all dependencies

OBJ = boot.o main.o io.asm.o io.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
INCLUDE = -I../include/
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJ)
	ld $(LDFLAGS) $(OBJ) -o kernel.elf

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $(INCLUDE) $< -o $@

