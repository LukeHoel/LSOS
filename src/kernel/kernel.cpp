#include "kernel.h"

#include "../bootstrap/c/bootstrap.cpp"

#include "utils.cpp"

#include "tty/tty.cpp"

#include "tty/terminal.cpp"

#include "interrupts/keyboard/keyboard.cpp"

#include "interrupts/interruptMapper.cpp"

#include "inputReceiver.cpp"

#include "memory/memory.cpp"

#include "unitTests/unitTests.cpp"

#if defined(__linux__)
#error                                                                         \
    "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with a ix86-elf compiler"
#endif

extern "C" void kernelMain(void) {
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
