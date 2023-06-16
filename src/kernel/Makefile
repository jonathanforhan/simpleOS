PROJECT_ROOT = ../..
BUILD = $(PROJECT_ROOT)/build/kernel

OBJ = ${shell find -name \*.[cS] -not -path "./arch/*" | sed -r 's/$$/.o/' | cut -c 3-}
HEADERS = ${shell find $(PROJECT_ROOT)/include/kernel/ -name \*.h}
INCLUDE = -I$(PROJECT_ROOT)/include/ -I$(PROJECT_ROOT)/include/kernel -I$(PROJECT_ROOT)/include/klib
LIB = -L$(PROJECT_ROOT)/lib -llibk

CC = gcc
CFLAGS = -std=c99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -Wall -Wextra -c
AS = gcc -c
LDFLAGS = -n -o kernel.elf -T link.ld

ifeq ($(target), i386)
OBJ += ${shell find arch/i386 -name \*.[cS] | sed -r 's/$$/.o/'}
ASFLAGS = -m32
CFLAGS += -m32
LDFLAGS += -melf_i386
else ifeq ($(target), x86_64)
OBJ += ${shell find arch/x86_64 -name \*.[cS] | sed -r 's/$$/.o/'}
ASFLAGS = -m64
CFLAGS += -m64
LDFLAGS += -melf_x86_64
else
$(error select target architecture with 'make target=[ i386 | x86_64 ]')
endif

OBJ_FULL_PATH = $(patsubst %, $(BUILD)/%, $(OBJ))

all: kernel.elf

kernel.elf: $(OBJ_FULL_PATH) $(HEADERS)
	@ld $(LDFLAGS) $(LIB) $(OBJ_FULL_PATH) -o $(BUILD)/kernel.elf
	@echo 'linking $(OBJ)'

$(BUILD)/%.c.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) $< -o $@
	@echo 'compiling $@'

$(BUILD)/%.S.o: %.S
	@$(AS) $(CFLAGS) $(INCLUDE) $< -o $@
	@echo 'assembling $@'

