# $@ = target file
# $< = first dependency
# $^ = all dependencies

KDIR = iso/boot

all: kernel

kernel:
	make -C src/
	cp src/kernel.elf $(KDIR)
	genisoimage -R                              \
	            -b boot/grub/stage2_eltorito    \
	            -no-emul-boot                   \
                -boot-load-size 4               \
                -A os                           \
                -input-charset utf8             \
                -quiet                          \
                -boot-info-table                \
                -o os.iso                       \
                iso

run: os.iso
	qemu-system-i386 -boot d -cdrom os.iso -m 512

clean:
	$(RM) src/*.o src/*.elf os.iso
