#include "shell.h"

#include "commandProcessor.cpp"
#include <cstdlib.h>

using namespace std;

namespace shell {
size_t terminalRow;
size_t terminalColumn;

void terminalPrintPrompt() {
  if (currentProgram == _shell) {
    printf("%s", prompt);
    // hide cursor offscreen
    updateCursor((VGA_WIDTH * VGA_HEIGHT) * -1, terminalRow);
  }
}

void terminalScroll() {
  // shift the lines up by one
  for (int y = 0; y < VGA_HEIGHT; y++) {
    for (int x = 0; x < VGA_WIDTH; x++) {
      ttyBuffer[screenIndex(x, y)] = ttyBuffer[screenIndex(x, y + 1)];
    }
  }
}

void terminalPutChar(char c, bool internal) {
  if (c == '\n') {
    // newline
    if (terminalRow < VGA_HEIGHT - 1) {
      terminalRow++;
    } else {
      terminalScroll();
    }

    terminalColumn = 0;

    if (!internal) {
      processCommand(terminalRow - 1);
      terminalPrintPrompt();
    }
  } else if (c == '\b') {
    // backspace
    if (!internal && terminalColumn <= promptLength) {
      return;
    }
    if (terminalColumn > 0) {
      terminalColumn--;
    }

    setScreenEntry(' ', 0, terminalColumn, terminalRow);
  } else {
    // allow last character in line to be delete
    if (terminalColumn < VGA_WIDTH - 1) {
      setScreenEntry(c, ttyColor, terminalColumn, terminalRow);
    }
    if (terminalColumn < VGA_WIDTH) {
      terminalColumn++;
    }
  }
}

void terminalPutS(const char *input) {
  for (size_t i = 0; i < strlen(input); i++) {
    terminalPutChar(input[i], true);
  }
}
void clearUtilityWidthBuffer() {
  for (size_t i = 0; i < VGA_WIDTH; i++) {
    utilityWidthBuffer[i] = ' ';
  }
}
void main() {
  clearScreen();
  clearUtilityWidthBuffer();
  terminalRow = 0;
  terminalColumn = 0;
  info({});
  terminalPrintPrompt();
}
} // namespace shell