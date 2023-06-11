# $@ = target file
# $< = first dependency
# $^ = all dependencies

BUILD = ../../build/src/kernel
OBJ = ${shell find . -name \*.[cS] -not -path "./arch/*" | sed -r 's/$$/.o/' | cut -c 3-}
HEADERS = ${shell find ../../include/kernel/ -name \*.h}
INCLUDE = -I../../include/ -I../../include/kernel -I../../include/lib
LIB = -L../../lib -llibk
CC = gcc
CFLAGS = -std=c99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -Wall -Wextra -c
AS = nasm
LDFLAGS = -n -o kernel.elf -T ../link.ld

ifeq ($(target), x86)
OBJ += ${shell find arch/i386 -name \*.[cS] | sed -r 's/$$/.o/'}
ASFLAGS = -felf32
CFLAGS += -m32
LDFLAGS += -melf_i386
else ifeq ($(target), x86_64)
OBJ += ${shell find arch/x86_64 -name \*.[cS] | sed -r 's/$$/.o/'}
ASFLAGS = -felf64
CFLAGS += -m64
LDFLAGS += -melf_x86_64
else
$(error select target architecture with 'make target=[ x86 | x86_64 ]')
endif

OBJ_FULL_PATH = $(patsubst %, $(BUILD)/%, $(OBJ))

all: kernel.elf

kernel.elf: $(OBJ_FULL_PATH) $(HEADERS)
	@ld $(LDFLAGS) $(LIB) $(INCLUDE) $(OBJ_FULL_PATH) -o $(BUILD)/kernel.elf
	@echo 'linking $(OBJ)'

$(BUILD)/%.c.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) $(LIB) $< -o $@
	@echo 'compiling $@'

$(BUILD)/%.S.o: %.S
	@$(AS) $(ASFLAGS) $< -o $@
	@echo 'assembling $@'

