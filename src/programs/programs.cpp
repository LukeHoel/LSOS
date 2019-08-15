

#define INPUT_TYPE_INTERNAL 0
#define INPUT_TYPE_USER 1
const char *prompt = ">";
#define promptLength 1

#include "shell/shell.cpp"

// // currently functionality is stuck inside of the shell, needs to be moved
// // elsewhere
// void printf(const char *data, ...) {
//   va_list arguments;
//   va_start(arguments, data);
//   shell::terminalPrintf(data, arguments);
// }

void runProgram(const char *name) {
  if (name == "shell") {
    shell::main();
  }
}

// // choose what to do depending on system state
// void putchar(char input) {
//   if (input > 0) {
//     shell::terminalPutChar(input, INPUT_TYPE_USER);
//   }
// }