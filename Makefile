# $@ = target file
# $< = first dependency
# $^ = all dependencies

BOOT_DIR = iso/boot
ISO_NAME = simpleOS.iso

all: kernel

kernel:
	make -C src/
	cp src/kernel.elf $(BOOT_DIR)
	grub-mkrescue -o $(ISO_NAME) iso/

run: $(ISO_NAME)
	qemu-system-x86_64 -cdrom $(ISO_NAME) -m 512

clean:
	$(RM) src/*.elf $(ISO_NAME)
	find -iname \*.o | xargs $(RM) $1
