#include "terminal.h"

#include <cstdlib.h>

using namespace std;

namespace programs {
size_t terminalRow;
size_t terminalColumn;
Terminal::Terminal() { Program::run("terminal"); }
void Terminal::terminalPrintPrompt() {
  printf("%s", prompt);
  // hide cursor offscreen
  updateCursor((VGA_WIDTH * VGA_HEIGHT) * -1, terminalRow);
}

void Terminal::terminalScroll() {
  // shift the lines up by one
  for (int y = 1; y < VGA_HEIGHT; y++) {
    for (int x = 0; x < VGA_WIDTH; x++) {
      ttyBuffer[screenIndex(x, y)] = ttyBuffer[screenIndex(x, y + 1)];
    }
  }
}

void Terminal::terminalPutChar(char c, bool internal) {
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

void Terminal::terminalPutS(const char *input) {
  for (size_t i = 0; i < strlen(input); i++) {
    terminalPutChar(input[i], true);
  }
}
void Terminal::clearUtilityWidthBuffer() {
  for (size_t i = 0; i < VGA_WIDTH; i++) {
    utilityWidthBuffer[i] = ' ';
  }
}
void Terminal::main() {
  clearUtilityWidthBuffer();
  terminalRow = 1;
  terminalColumn = 0;
  info();
  terminalPrintPrompt();
}
void readLine(size_t rowNumber, char *lineContent) {

  int foundEnd = 0;
  for (int i = VGA_WIDTH; i >= 0; i--) {
    // get current line
    char current = ttyBuffer[i + (VGA_WIDTH * rowNumber)];
    if (!foundEnd) {
      if (current == ' ') {
        lineContent[i] = 0;
      } else {
        foundEnd = 1;
      }
    }
    if (foundEnd) {
      lineContent[i] = current;
    }
  }
}

// takes in string, outputs split string by spaces, returns int
int splitCommand(char *lineContent, char splitContent[VGA_WIDTH][VGA_WIDTH]) {

  int i = 0;
  int j = 0;
  for (size_t k = promptLength; k < strlen(lineContent); k++) {

    if (lineContent[k] == ' ') {
      // end string with null terminator
      splitContent[i][j] = '\0';
      i++;
      j = 0;
    } else {
      splitContent[i][j++] = lineContent[k];
    }
  }

  // add null terminator to end
  splitContent[i][j] = '\0';
  return i + 1;
}
// commands
void Terminal::processCommand(size_t rowNumber) {

  // read the line into the lineContent variable
  char lineContent[VGA_WIDTH];
  readLine(rowNumber, lineContent);
  // send into parser
  commandData data;
  data.count = splitCommand(lineContent, data.words);
  executeCommand(data);
}
void Terminal::executeCommand(commandData data) {
  char *commandName = data.words[0];
  if (strcmp(commandName, "info") == 0) {
    info();
  } else if (strcmp(commandName, "echo") == 0) {
    echo(data);
  } else {
    terminalPutS("Command not found\n");
  }
}
void Terminal::info() {
  terminalPutS("Simple OS ");
  terminalPutS("Version ");
  terminalPutS(VERSION);
  terminalPutS("\n");
}

void Terminal::echo(commandData data) {
  // start at 1 because 0 is the command name
  for (size_t i = 1; i < data.count; i++) {
    terminalPutS(data.words[i]);
    terminalPutS(" ");
  }
  terminalPutChar('\n', true);
}

} // namespace programs