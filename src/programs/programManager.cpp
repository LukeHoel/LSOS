

#include "programManager.h"
#include "program/program.cpp"

programs::Program *currentProgram;

#include "terminal/terminal.cpp"

namespace programs {

Terminal terminal;

void runProgram(const char *name) { terminal = Terminal(); }

void sendKeypressToActiveProgram(int keyCode, char mappedKeyCode) {
  terminal.receiveKeyPress(keyCode, mappedKeyCode);
}
} // namespace programs