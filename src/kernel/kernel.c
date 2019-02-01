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
#include "c/memory/memory.c"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void fillPointer(char *ptr, char value, size_t length){
	size_t i;
	for(i = 0; i < length; i++){
		ptr[i] = value;
	}
}

void printPointer(char *ptr, size_t length){
	size_t i;
	for(i = 0; i < length; i ++){
		terminalPrintf("%c", ptr[i]);
	}
	terminalPrintf("\n");
}

void testMalloc(){
	char *test = malloc(sizeof(char) * 10000);
	char *test2 = malloc(sizeof(char) * 5);
	char *test3 = malloc(sizeof(char) * 700);
	char *test4 = malloc(sizeof(char) * 100);
//	fillPointer(test, 'a', 100);	
//	fillPointer(test2, 'b', 5);	
//	fillPointer(test3, 'c', 100);	
//
//	printPointer(test, 100);	
//	printPointer(test2, 5);	
//	printPointer(test3, 100);	
	terminalPrintf("\n");
	terminalPrintf("%d\n", (long)test);
	terminalPrintf("%d\n", (long)test2);
	terminalPrintf("%d\n", (long)test3);
	terminalPrintf("%d\n", (long)test4);
}

void kernelMain(void) 
{
    	gdtInit();
	idtInit();
    	ttyInit();
	terminalInit();
	kbInit();
	terminalPrintPrompt();

	//testMalloc();

	while(1);
}
