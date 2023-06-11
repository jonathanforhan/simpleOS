# $@ = target file
# $< = first dependency
# $^ = all dependencies

OBJ = ${shell find -name \*.[cS] -not -path "./arch/*" | sed -r 's/(.*).[cS]/\1.o/g'}
HEADERS = ${shell find ../include -name \*.h}
CC = gcc
CFLAGS = -std=c99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -Wall -Wextra -c
INCLUDE = -I../include/
LDFLAGS = -n -o kernel.elf -T link.ld
AS = nasm

ifeq ($(target), x86)
OBJ += ${shell find arch/i386 -name \*.[cS] | sed -r 's/(.*).[cS]/\1.o/g'}
ASFLAGS = -felf32
CFLAGS += -m32
LDFLAGS += -melf_i386
else ifeq ($(target), x86_64)
OBJ += ${shell find arch/x86_64 -name \*.[cS] | sed -r 's/(.*).[cS]/\1.o/g'}
ASFLAGS = -felf64
CFLAGS += -m64
LDFLAGS += -melf_x86_64
else
$(error select target architecture with 'make target=[ x86 | x86_64 ]')
endif

all: kernel.elf

kernel.elf: $(OBJ) $(HEADERS)
	ld $(LDFLAGS) $(OBJ) -o kernel.elf

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

%.o: %.S
	$(AS) $(ASFLAGS) $< -o $@

