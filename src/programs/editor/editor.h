#ifndef EDITOR_H
#define EDITOR_H
namespace programs {
class Editor : Program {
public:
  Editor(string name);
  void main();
  void receiveKeyPress(int keyCode, char mappedKeyCode) {
    if (mappedKeyCode == 'q') {
      Program::exit();
    }
  }
};
} // namespace programs
#endif