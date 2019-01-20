#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

//my stuff
#include "extrafiles/tty.c"
#include "extrafiles/idt.c"
#include "extrafiles/keyboard.c"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) 
{
        terminal_initialize();
	idt_init();
	kb_init();
	while(1);
}
