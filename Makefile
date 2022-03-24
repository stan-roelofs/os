C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c util/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h util/*.h)

# TODO: sources depend on header files

OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

all: os-image.bin

run: all
	qemu-system-x86_64 os-image.bin

debug: all
	qemu-system-x86_64 os-image.bin -s -S &
	gdb -x .gdbinit

os-image.bin: boot/boot.bin kernel.bin
	cat $^ > os-image.bin
	dd if=/dev/zero obs=512 count=15 >> os-image.bin

kernel.bin : kernel/kernel_entry.o ${OBJ}
	ld -T script.ld -m elf_i386 -o $@ $^ --oformat binary

%.o : %.asm
	nasm $< -f elf -o $@

%.o : %.c
	gcc -m32 -I include/ -fno-PIC --freestanding -c $< -o $@ -ggdb

%.bin : %.asm
	nasm $< -f bin -I boot/ -o $@

clean:
	rm -fr *.bin *.dis *.o *.map *.tmp *.temp
	rm -fr kernel/*.o boot/*.bin drivers/*.o cpu/*.o include/*.0

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@