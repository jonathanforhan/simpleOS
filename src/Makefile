# $@ = target file
# $< = first dependency
# $^ = all dependencies

OBJ = ${shell find -name \*.[cS] | sed -r 's/(.*).[cS]/\1.o/g'}
HEADERS = ${shell find ../include -name \*.h}
CC = gcc
CFLAGS = -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -Wall -Wextra -c
INCLUDE = -I../include/
LDFLAGS = -n -o kernel.elf -T link.ld
AS = nasm
ASFLAGS = -felf64

all: kernel.elf

kernel.elf: $(OBJ) $(HEADERS)
	ld $(LDFLAGS) $(OBJ) -o kernel.elf

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

%.o: %.S
	$(AS) $(ASFLAGS) $< -o $@

