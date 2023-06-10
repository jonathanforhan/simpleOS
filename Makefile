# $@ = target file
# $< = first dependency
# $^ = all dependencies

BOOT_DIR = iso/boot

all: kernel

kernel:
	make -C src/
	cp src/kernel.elf $(BOOT_DIR)
	grub-mkrescue -o simpleOS.iso iso/

run: simpleOS.iso
	qemu-system-x86_64 -cdrom simpleOS.iso -m 512

clean:
	$(RM) src/**/*.o src/*.elf simpleOS.iso
