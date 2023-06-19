BOOT_DIR = iso/boot
ISO_NAME = simpleOS.iso
BUILD = build

all: kernel

kernel:
	@mkdir -p $(BUILD)/
	@cd src/ && find -type d -exec mkdir -p ../$(BUILD)/{} \;
	@bear -- make -C src
	@cp $(BUILD)/kernel/kernel.elf $(BOOT_DIR)
	@grub-mkrescue -o $(ISO_NAME) iso/

run: $(ISO_NAME)
	qemu-system-x86_64 -cdrom $(ISO_NAME) -m 512

clean:
	$(RM) src/*.elf $(ISO_NAME)
	find -type f -name \*.[ao] | xargs rm -f $1
