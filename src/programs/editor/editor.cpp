#include "editor.h"
namespace editor {
void drawFrame() {
  for (size_t i = 0; i < VGA_WIDTH; i++) {
    setScreenEntry('a', VGA_COLOR_BLUE, titleBarColor, i, 0);
  }
  drawTitle();
}
void drawTitle() {
  for (size_t i = 0; i < strlen(title); i++) {
    setScreenEntry(title[i], VGA_COLOR_LIGHT_GREY, titleBarColor, i, 0);
  }
}
void main() {
  clearScreen();
  drawFrame();
}
void receiveKeyPress(int keyCode, char mappedKeyCode) {
  if (mappedKeyCode == 'q') {
    exit();
  }
}
void exit() { runProgram("shell"); }
} // namespace editor
