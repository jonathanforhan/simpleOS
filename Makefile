# $@ = target file
# $< = first dependency
# $^ = all dependencies

BOOT_DIR = iso/boot
ISO_NAME = simpleOS.iso
BUILD = build

all: kernel

kernel:
	@mkdir -p build/
	@find src/ -type d -exec mkdir -p build/{} \;
	@make -C src/
	@cp $(BUILD)/kernel.elf $(BOOT_DIR)
	grub-mkrescue -o $(ISO_NAME) iso/

run: $(ISO_NAME)
	qemu-system-x86_64 -cdrom $(ISO_NAME) -m 512

clean:
	$(RM) src/*.elf $(ISO_NAME)
