#ifndef EDITOR_H
#define EDITOR_H
using namespace std;
namespace editor {
const char *title = "Editor";
const enum vgaColor titleBarColor = VGA_COLOR_BLUE;
void drawFrame();
void drawTitle();
void main();
void exit();
void receiveKeyPress(int keyCode, char mappedKeyCode);
} // namespace editor
#endif
