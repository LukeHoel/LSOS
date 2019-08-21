#include "editor.h"
using namespace std;
namespace programs {
void putStringAtLocation(string str, size_t x, size_t y) {
  for (size_t i = 0; i < str.length(); i++) {
    setScreenEntry(str[i], VGA_COLOR_LIGHT_GREY, x + i, y);
  }
}
Editor::Editor(string name) { run(name.c_str()); }
void Editor::main() { putStringAtLocation("Mode: Normal ", 0, VGA_HEIGHT - 1); }

void Editor::receiveKeyPress(int keyCode, unsigned char mappedKeyCode) {
  switch (keyCode) {
  case upKey:
    if (cursorY > 1) {
      updateCursor(cursorX, --cursorY);
    }
    break;
  case downKey:
    if (cursorY < VGA_HEIGHT - 2) {
      updateCursor(cursorX, ++cursorY);
    }
    break;
  case leftKey:
    if (cursorX > 0) {
      updateCursor(--cursorX, cursorY);
    }
    break;
  case rightKey:
    if (cursorX < VGA_WIDTH - 1) {
      updateCursor(++cursorX, cursorY);
    }
    break;
  case escapeKey:
    // Program::exit();
    putStringAtLocation("Mode: Normal ", 0, VGA_HEIGHT - 1);
    mode = NORMAL;
    break;
    break;
  default:
    switch (mode) {
    case (NORMAL):
      switch (mappedKeyCode) {
      case ('i'):
        putStringAtLocation("Mode: Insert ", 0, VGA_HEIGHT - 1);
        mode = INSERT;
        break;
      case (';'):
        putStringAtLocation("Mode: Command", 0, VGA_HEIGHT - 1);
        mode = COMMAND;
        break;
      }
      break;
    case (INSERT):
      if (mappedKeyCode == '\b') {
        setScreenEntry(' ', VGA_COLOR_LIGHT_GREY, cursorX, cursorY);
        if (cursorX > 0) {
          updateCursor(--cursorX, cursorY);
        }
      } else {

        setScreenEntry(mappedKeyCode, VGA_COLOR_LIGHT_GREY, cursorX, cursorY);
        if (cursorX < VGA_WIDTH - 1) {
          updateCursor(++cursorX, cursorY);
        }
      }
      break;
    case (COMMAND):
      switch (mappedKeyCode) {
      case ('q'):
        Program::exit();
        break;
      }
      break;
    }
    break;
  }
}
} // namespace programs