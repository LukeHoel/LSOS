#include "../cstdio.h"
void sendPutCharToProgram(char input);
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
    tempString[maxLength - i] = digits[in % 10];
    in /= base;
  }
  tempString[maxLength] = '\0';
  return tempString;
}
void printf(const char *data, ...) {

  va_list arguments;
  va_start(arguments, data);

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
        puts(va_arg(arguments, char *));
        break;
      case ('d'):
        puts(convertNumber(va_arg(arguments, int)));
        break;
      case ('x'):
        puts(convertNumber(va_arg(arguments, int), "hex"));
        break;
      default:
        putchar(data[i]);
        break;
      }
    }
  }

  va_end(arguments);
}
void putchar(char input) { sendPutCharToProgram(input); }
void puts(char *input) {
  for (size_t i; i < strlen(input); i++) {
    putchar(input[i]);
  }
}
void sprintf(char *buffer, const char *data, ...) {

  va_list arguments;
  va_start(arguments, data);

  for (size_t i = 0; i < strlen(data); i++) {

    if (data[i] != '%') {
      putchar(data[i]);
    } else {
      // go right ahead to next character
      i++;
      // switch to parser for whatever data type this is
      switch (data[i]) {
      case ('c'):
        sputchar(buffer, i, va_arg(arguments, int));
        break;
      case ('s'):
        sputs(buffer, i, va_arg(arguments, char *));
        break;
      case ('d'):
        sputs(buffer, i, convertNumber(va_arg(arguments, int)));
        break;
      case ('x'):
        sputs(buffer, i, convertNumber(va_arg(arguments, int), "hex"));
        break;
      default:
        sputchar(buffer, i, data[i]);
        break;
      }
    }
  }

  va_end(arguments);
}
void sputchar(char *buffer, int i, char input) { buffer[i] = input; }
void sputs(char *buffer, int i, char *input) {
  for (size_t o; o < strlen(input); o++) {
    sputchar(buffer, i, input[o]);
    i++;
  }
}
} // namespace std