all: os-image.bin

run: all
	qemu-system-x86_64 os-image.bin

os-image.bin: boot.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin : kernel_entry.o kernel.o
	ld -T script.ld -m elf_i386 -o kernel.bin $^ --oformat binary
	dd if=/dev/zero count=1 >> kernel.bin

kernel.o : kernel.c
	gcc -m32 -fno-PIC -ffreestanding -c $< -o $@

kernel_entry.o : kernel_entry.asm
	nasm $< -f elf -o $@

boot.bin: boot.asm
	nasm $< -f bin -o $@

clean:
	rm -fr *.bin *.dis *.o *.map

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@