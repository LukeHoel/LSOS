#include "../cstdio.h"
namespace programs {
void sendKeypressToActiveProgram(int keyCode, char mappedKeyCode);
}
namespace std {
// Don't use outside of here, it keeps one char* for all conversions
const int maxLength = 13;
char tempString[maxLength + 1];
char *convertNumber(int in, const char *type = "decimal") {
  // Allow conversion of decimal or hex (default to decimal)
  const int base = type == "hex" ? 16 : 10;
  char digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  // Enough to store a long long

  int length = 1;
  // first, get length of input number
  int temp = in;
  while (temp > base - 1) {
    temp /= base;
    length++;
  }

  // Print in reverse
  int i;
  for (i = 1; i <= length; i++) {
    tempString[length - i] = digits[in % base];
    in /= base;
  }
  tempString[length] = '\0';
  return tempString;
}
void printf(const char *data, ...) {

  va_list arguments;
  va_start(arguments, data);
  char *temp;
  for (size_t i = 0; i < strlen(data); i++) {
    if (data[i] != '%') {
      putchar(data[i]);
    } else {
      // go right ahead to next character
      i++;
      // switch to parser for whatever data type this is
      switch (data[i]) {
      case ('c'):
        putchar(va_arg(arguments, int));
        break;
      case ('s'):
        printf(va_arg(arguments, char *));
        break;
      case ('d'):
        printf(convertNumber(va_arg(arguments, int)));
        break;
      case ('x'):
        printf(convertNumber(va_arg(arguments, int), "hex"));
        break;
      default:
        putchar(data[i]);
        break;
      }
    }
  }

  va_end(arguments);
}
void putchar(char input) { programs::sendKeypressToActiveProgram(-1, input); }
void puts(char *input) {
  for (size_t i; i < strlen(input); i++) {
    putchar(input[i]);
  }
}
} // namespace std