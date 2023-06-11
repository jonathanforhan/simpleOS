# $@ = target file
# $< = first dependency
# $^ = all dependencies

.PHONY: kernel lib 

kernel: lib
	@make -C kernel/

lib:
	@make -C lib/
