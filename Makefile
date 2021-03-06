ASMDIR := src/bootstrap/lowlevel
KERNELMAIN := src/kernel/kernel.cpp
LINKERFILE := src/bootstrap/link.ld

OSNAME := simple-os

BOOTDIR := build/boot

WARNINGS := -Wall

CFLAGS := -std=c++17 -ffreestanding -Wextra -fno-exceptions -fno-rtti

# to replace with proper packaging later?
STDLIBH := $(shell find src/std -name '*.h')
STDLIBCPP := $(shell find src/std -name '*.cpp')

# to build bin (for emulation use, much smaller file size)
all:  clean buildfolder buildstandardlibrary boot.o kernel.o link 
# to build for grub (bootable on bare hardware) 
grub:  clean buildfolder buildstandardlibrary boot.o kernel.o link isodir iso

buildstandardlibrary:
	@mkdir build/standardlibrary \
	&& i686-elf-g++ $(CFLAGS) -nostdlib -c $(STDLIBCPP) \
	&& mv *.o build/standardlibrary

buildfolder:
	@mkdir -p build

boot.o:
	@nasm -f elf32 $(ASMDIR)/boot.asm -i $(ASMDIR) -o build/boot.o	

kernel.o:
	@i686-elf-g++ -c $(KERNELMAIN) $(CFLAGS) -I src/std -o build/kernel.o

link:	
	@i686-elf-g++ -T $(LINKERFILE) -o $(OSNAME).bin -ffreestanding -O2 -nostdlib build/standardlibrary/* build/boot.o build/kernel.o -lgcc

isodir:
	@mkdir -p $(BOOTDIR)/grub \
	&& mv $(OSNAME).bin $(BOOTDIR) \
	&& cp src/bootstrap/grub.cfg $(BOOTDIR)/grub/grub.cfg

iso:
	@grub-mkrescue -o $(OSNAME).iso build &> build/grubisobuild.log 

clean:
	@rm -f $(OSNAME).bin $(OSNAME).iso
	@rm -rf build 
