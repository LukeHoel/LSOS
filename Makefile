ASMDIR := src/kernel/asm
KERNELMAIN := src/kernel/kernel.c
LINKERFILE := src/kernel/link.ld

OUTFILENAME := lsos.bin

WARNINGS := -Wall

CFLAGS := -std=gnu99 -ffreestanding $(WARNINGS)

all:  clean boot.o kernel.o link

boot.o:
	@nasm -f elf32 $(ASMDIR)/boot.asm -i $(ASMDIR) -o boot.o	
kernel.o:
	@i686-elf-gcc -c $(KERNELMAIN) $(CFLAGS) -o kernel.o

link:	
	@i686-elf-gcc -T $(LINKERFILE) -o $(OUTFILENAME) -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

clean:
	@rm -f *.o 
