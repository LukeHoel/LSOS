#ifndef EDITOR_H
#define EDITOR_H
namespace programs {
class Editor : Program {
  size_t cursorX = 0;
  size_t cursorY = 1;

public:
  Editor(string name);
  void main();
  void receiveKeyPress(int keyCode, unsigned char mappedKeyCode) {
    if (mappedKeyCode == 'q') {
      Program::exit();
    }
  }
  void receiveArrowKey(unsigned char direction) {
    switch (direction) {
    case upKey:
      if (cursorY > 1)
        cursorY--;
      break;
    case downKey:
      if (cursorY < VGA_HEIGHT - 1)
        cursorY++;
      break;
    case leftKey:
      if (cursorX > 0)
        cursorX--;
      break;
    case rightKey:
      if (cursorX < VGA_WIDTH - 1)
        cursorX++;
      break;
    }
    setScreenEntry(' ', VGA_COLOR_LIGHT_GREY, cursorX, cursorY);
  };
};
} // namespace programs
#endif