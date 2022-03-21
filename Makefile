C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

# TODO: sources depend on header files

OBJ = ${C_SOURCES:.c=.o}

all: os-image.bin

run: all
	qemu-system-x86_64 os-image.bin

os-image.bin: boot/boot.bin kernel.bin
	cat $^ > os-image.bin
	dd if=/dev/zero count=1 >> os-image.bin

kernel.bin : kernel/kernel_entry.o ${OBJ}
	ld -T script.ld -m elf_i386 -o $@ $^ --oformat binary

%.o : %.c
	gcc -m32 -fno-PIC --freestanding -c $< -o $@

%.o : %.asm
	nasm $< -f elf -o $@

%.bin : %.asm
	nasm $< -f bin -I boot/ -o $@

clean:
	rm -fr *.bin *.dis *.o *.map *.tmp *.temp
	rm -fr kernel/*.o boot/*.bin drivers/*.o

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@