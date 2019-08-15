#include "string.h"
namespace std {

void to_string(int in) {
  const int base = 10;
  char digits[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  int length = 1;
  size_t position = terminalColumn;

  // first, get length of input number
  int temp = in;
  while (temp > base - 1) {
    temp /= base;
    length++;
  }

  // printing out normally would give us a reversed version of what we want...
  // not good enough print out the reverse-in reverse, to get the right way
  // around
  int i;
  for (i = 1; i <= length; i++) {
    ttyBuffer[screenIndex((position + length) - i, terminalRow)] =
        vgaEntry(digits[in % 10], 7);
    in /= base;
    if (terminalColumn < VGA_WIDTH) {
      terminalColumn++;
      updateCursor(terminalColumn, terminalRow);
    }
  }
}
} // namespace std
