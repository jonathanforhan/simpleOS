# $@ = target file
# $< = first dependency
# $^ = all dependencies

BUILD = ../../build/src/lib
OBJ = ${shell find . -name \*.[cS] -not -path "./arch/*" | sed -r 's/$$/.o/' | cut -c 3-}
HEADERS = ${shell find ../../include/lib -name \*.h}
INCLUDE = -I../../include/lib
LIB = ../../lib
CC = gcc
CFLAGS = -std=c99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -Wall -Wextra -c
AS = nasm
ARFLAGS = rcs 

ifeq ($(target), x86)
ASFLAGS = -felf32
CFLAGS += -m32
else ifeq ($(target), x86_64)
ASFLAGS = -felf64
CFLAGS += -m64
else
$(error select target architecture with 'make target=[ x86 | x86_64 ]')
endif

OBJ_FULL_PATH = $(patsubst %, $(BUILD)/%, $(OBJ))

all: liblibk.a

liblibk.a: $(OBJ_FULL_PATH) $(HEADERS)
	@ar $(ARFLAGS) $(LIB)/liblibk.a $(OBJ_FULL_PATH)
	@echo 'linking $(OBJ)'

$(BUILD)/%.c.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) $(LIB) $< -o $@
	@echo 'compiling $@'

$(BUILD)/%.S.o: %.S
	@$(AS) $(ASFLAGS) $< -o $@
	@echo 'assembling $@'

