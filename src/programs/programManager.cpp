

#include "shell/shell.cpp"

enum Programs { _shell = 1 };

int currentProgram = 0;

void runProgram(const char *name) {
  if (name == "shell") {
    currentProgram = _shell;
    shell::main();
  }
}

void sendPutCharToProgram(char input) {
  switch (currentProgram) {

  case (_shell):
    shell::terminalPutChar(input);
    break;
  }
}