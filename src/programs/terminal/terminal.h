#ifndef TERMINAL_H
#define TERMINAL_H
#include <string.h>
using namespace std;
namespace programs {
const char *prompt = ">";
#define promptLength 1
class commandData {
public:
  char words[VGA_WIDTH][VGA_WIDTH];
  size_t count;
};

struct command {
  const char *name;
  void (*function)(commandData);
};

class Terminal : Program {
public:
  Terminal();
  // Overridden base class stuff
  void receiveKeyPress(int keyCode, char mappedKeyCode) {
    terminalPutChar(mappedKeyCode);
  };
  // Random access point for use in commands. Not stable
  char utilityWidthBuffer[VGA_WIDTH];
  void clearUtilityWidthBuffer();
  void terminalPrintPrompt();
  void terminalScroll();
  void terminalPutChar(char c, bool internal = false);
  void terminalPutS(const char *input);
  void main();
  void exit(){};
  // commands
  void executeCommand(commandData data);
  void processCommand(size_t rowNumber);
  void info();
  void echo(commandData data);
};
} // namespace programs
#endif