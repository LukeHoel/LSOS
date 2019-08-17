#include "kernel.h"

// clang-format off
#include "../bootstrap/highlevel/boot.cpp"
#include "utils.cpp"
#include "screen/screen.cpp"
#include "interrupts/keyboard/keyboard.cpp"
#include "interrupts/interruptMapper.cpp"
#include "../programs/programManager.cpp"
#include "unitTests/unitTests.cpp"
// clang-format on

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
  runUnitTests(); // will print out if anything went wrong
  while (1) {
    // Loop forever, waiting for interrupts
  }
}
