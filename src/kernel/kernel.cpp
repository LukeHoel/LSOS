#include "kernel.h"

using namespace std;

// clang-format off
#include "../bootstrap/highlevel/boot.cpp"
#include "../bootstrap/highlevel/icxxabi.cpp"
#include "utils.cpp"
#include "screen/screen.cpp"
#include "../programs/programManager.cpp"
#include "interrupts/keyboard/keyboard.cpp"
#include "interrupts/interruptMapper.cpp"
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
  programs::runProgram("terminal");
  runUnitTests(); // will print out if anything went wrong
  while (1) {
    // Loop forever, waiting for interrupts
  }
}
