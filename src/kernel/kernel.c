#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "c/tty.c"
#include "c/idt.c"
#include "c/keyboard.c"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernelMain(void) 
{
    	terminalInitialize();
	idtInit();
	kbInit();
	while(1);
}
