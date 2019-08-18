

#include "programManager.h"

#include "editor/editor.cpp"
#include "shell/shell.cpp"

void runProgram(const char *name) {
  if (name == "shell") {
    currentProgram = _shell;
    shell::main();
  } else if (name == "editor") {
    currentProgram = _editor;
    editor::main();
  }
}

void sendKeypressToActiveProgram(int keyCode, char mappedKeyCode) {
  if (currentProgram == _shell) {
    shell::terminalPutChar(mappedKeyCode);
  } else if (currentProgram == _editor) {
    editor::receiveKeyPress(keyCode, mappedKeyCode);
  }
}
void sendPutCharToProgram(char input) { shell::terminalPutChar(input); }