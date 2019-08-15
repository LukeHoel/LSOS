// TODO remove later and replace with proper header files
namespace shell {
void terminalPrintf(const char *data, ...);
}
#include "commandProcessor.cpp"

namespace shell {
size_t terminalRow;
size_t terminalColumn;

void terminalPrintPrompt() {
  terminalPrintf("%s", prompt);
  // hide cursor offscreen
  updateCursor((VGA_WIDTH * VGA_HEIGHT) * -1, terminalRow);
}

void terminalScroll() {
  // shift the lines up by one
  for (int y = 0; y < VGA_HEIGHT; y++) {
    for (int x = 0; x < VGA_WIDTH; x++) {
      ttyBuffer[screenIndex(x, y)] = ttyBuffer[screenIndex(x, y + 1)];
    }
  }
}

void terminalPutChar(char c, int type) {
  if (c == '\n') {
    // newline
    if (terminalRow < VGA_HEIGHT - 1) {
      terminalRow++;
    } else {
      terminalScroll();
    }

    terminalColumn = 0;

    if (type == INPUT_TYPE_USER) {
      processCommand(terminalRow - 1);
      terminalPrintPrompt();
    }
  } else if (c == '\b') {
    // backspace
    if (type == INPUT_TYPE_USER && terminalColumn <= promptLength) {
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

void terminalWrite(const char *data, size_t size) {
  for (size_t i = 0; i < size; i++)
    terminalPutChar(data[i], INPUT_TYPE_INTERNAL);
}

void terminalWriteString(const char *data) {
  terminalWrite(data, strlen(data));
}

void terminalPrintf() {}
void main() {
  terminalRow = 0;
  terminalColumn = 0;
  terminalPrintPrompt();
}
} // namespace shell