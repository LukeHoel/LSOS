#include "kernel.h"

#include "../bootstrap/c/bootstrap.c"

#include "utils.c"

#include "tty/tty.c"

#include "tty/terminal.c"

#include "interrupts/keyboard/keyboard.c"

#include "interrupts/interruptMapper.c"

#include "inputReceiver.c"

#include "memory/memory.c"

#include "unitTests/unitTests.c"

#if defined(__linux__)
#error                                                                         \
    "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with a ix86-elf compiler"
#endif

void kernelMain(void) {
  bootstrap();
  ttyInit();
  terminalInit();
  kbInit();
  terminalPrintPrompt();
  runUnitTests(); // will print out if anything went wrong
  while (1) {
    // Loop forever, waiting for interrupts
  }
}
