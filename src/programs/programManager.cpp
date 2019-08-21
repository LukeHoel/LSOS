

#include "programManager.h"

#include "program/program.cpp"

#include "editor/editor.cpp"
#include "terminal/terminal.cpp"

namespace programs {

string currentProgram;

Terminal terminal;
Editor editor("editor");

void runProgram(string name) {

  currentProgram = name;

  if (currentProgram == "terminal") {
    terminal = Terminal();
  } else {
    currentProgram = "editor";
    editor = Editor(name);
  }
}

void sendKeypressToActiveProgram(int keyCode, unsigned char mappedKeyCode) {
  if (currentProgram == "terminal") {
    terminal.receiveKeyPress(keyCode, mappedKeyCode);
  } else {
    editor.receiveKeyPress(keyCode, mappedKeyCode);
  }
}
} // namespace programs