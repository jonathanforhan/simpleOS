PROJECT_ROOT = ../..

BUILD = $(PROJECT_ROOT)/build/klib
OBJ = ${shell find -name \*.[cS] -not -path "./arch/*" | sed -r 's/$$/.o/' | cut -c 3-}
HEADERS = ${shell find $(PROJECT_ROOT)/include/klib -name \*.h}
INCLUDE = -I$(PROJECT_ROOT)/include/klib
CC = gcc
CFLAGS = -std=c99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -no-pie -Wall -Wextra -c
AS = gcc -c
ARFLAGS = rcs 

ifeq ($(target), i386)
ASFLAGS = -m32
CFLAGS += -m32
else ifeq ($(target), x86_64)
ASFLAGS = -m64
CFLAGS += -m64
else
$(error select target architecture with 'make target=[ i386 | x86_64 ]')
endif

OBJ_FULL_PATH = $(patsubst %, $(BUILD)/%, $(OBJ))

all: liblibk.a

liblibk.a: $(OBJ_FULL_PATH) $(HEADERS)
	@ar $(ARFLAGS) $(PROJECT_ROOT)/lib/liblibk.a $(OBJ_FULL_PATH)
	@echo 'linking $(OBJ)'

$(BUILD)/%.c.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) $(LIB) $< -o $@
	@echo 'compiling $@'

$(BUILD)/%.S.o: %.S
	@$(AS) $(ASFLAGS) $(INCLUDE) $< -o $@
	@echo 'assembling $@'


