#include "program.h"
namespace programs {
void Program::run(const char *programName) {
  clearScreen();
  drawBar(programName);
  main();
}
void Program::drawBar(const char *programName) {
  for (size_t i = 0; i < VGA_WIDTH; i++) {
    setScreenEntry('m', VGA_COLOR_BLUE, VGA_COLOR_BLUE, i, 0, false);
  }
  drawTitle(programName);
}
void Program::drawTitle(const char *programName) {
  for (size_t i = 0; i < strlen(programName); i++) {
    setScreenEntry(programName[i], VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLUE, i, 0,
                   false);
  }
}
void Program::main() {}
void Program::exit() { runProgram("shell"); }
} // namespace programs
