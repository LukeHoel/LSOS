#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

//my stuff
#include "extrafiles/tty.c"

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
        /* Initialize terminal interface */
        terminal_initialize();
     
        /* Newline support is left as an exercise. */
        //terminal_writestring("Hello there!\n");
        //kprintf("the char is: %c\n", '*');
        kprintf("the number is: %d\n", 12345);
        kprintf("the string is: %s\n", "somebody once told me");
        kprintf("Hello there, %s! you are %c bold one. Also a number: %d", "General Kenobi", 'a', 111256);
}
