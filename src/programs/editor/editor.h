#ifndef EDITOR_H
#define EDITOR_H
namespace programs {
enum possibleModes { NORMAL, INSERT, COMMAND };
class Editor : Program {
  size_t cursorX = 0;
  size_t cursorY = 1;
  int mode = NORMAL;

public:
  Editor(string name);
  void main();
  void receiveKeyPress(int keyCode, unsigned char mappedKeyCode);
};
} // namespace programs
#endif