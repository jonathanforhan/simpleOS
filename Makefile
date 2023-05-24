# $@ = target file
# $< = first dependency
# $^ = all dependencies

SRC=src
BUILD=build

# First rule is the one executed when no parameters are fed to the Makefile
all: run

$(BUILD)/kernel.bin: $(SRC)/kernel_entry.o $(SRC)/kernel.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

$(SRC)/kernel_entry.o: $(SRC)/kernel_entry.s
	nasm $< -f elf -o $@

$(SRC)/kernel.o: $(SRC)/kernel.c
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

$(BUILD)/mbr.bin: $(SRC)/mbr.s
	nasm $< -f bin -o $@

$(BUILD)/os-image.bin: $(BUILD)/mbr.bin $(BUILD)/kernel.bin
	cat $^ > $@

run: $(BUILD)/os-image.bin
	qemu-system-i386 -display gtk -fda $<

clean:
	$(RM) *.bin *.o *.dis
