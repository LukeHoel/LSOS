#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "kernel.h"
#include "c/utils.c"
#include "c/tty/tty.c"
#include "c/tty/terminal.c"
#include "c/gdt.c"
#include "c/idt.c"
#include "c/interrupts/keyboard/keyboard.c"
#include "c/interrupts/interruptMapper.c"
#include "c/inputReceiver.c"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernelMain(void) 
{
    	gdtInit();
	idtInit();
    	ttyInit();
	terminalInit();
	kbInit();
	terminalPrintPrompt();
	while(1);
}
