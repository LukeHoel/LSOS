#include "kernel.h"

#include "../bootstrap/highlevel/boot.cpp"

#include "utils.cpp"

#include "tty/screen.cpp"

#include "interrupts/keyboard/keyboard.cpp"

#include "interrupts/interruptMapper.cpp"

#include "../programs/programs.cpp"

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
  clearScreen();
  initKeyboard();
  runProgram("shell");
  // TODO make shell not own the printf so it can be used elsewhere
  runUnitTests(); // will print out if anything went wrong
  while (1) {
    // Loop forever, waiting for interrupts
  }
}
