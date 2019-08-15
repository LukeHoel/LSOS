#include "cstdio.h"
namespace std {
void printf(const char *data, ...) {

  va_list arguments;
  va_start(arguments, data);

  for (size_t i = 0; i < strlen(data); i++) {
    if (data[i] != '%') {
      terminalPutChar(data[i], INPUT_TYPE_INTERNAL);
    } else {
      // go right ahead to next character
      i++;
      // switch to parser for whatever data type this is
      switch (data[i]) {
      case ('c'):
        terminalPutChar(va_arg(arguments, int), INPUT_TYPE_INTERNAL);
        break;
      case ('s'):
        terminalWriteString(va_arg(arguments, const char *));
        break;
      case ('d'):
        printNumber(va_arg(arguments, int), DECIMAL);
        break;
      case ('x'):
        printNumber(va_arg(arguments, int), HEX);
        break;
      default:
        terminalPutChar(data[i], INPUT_TYPE_INTERNAL);
        break;
      }
    }
  }

  va_end(arguments);
}
} // namespace std