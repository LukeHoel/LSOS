#include <string.h>

namespace programs {
void runProgram(const string name);
void sendKeypressToActiveProgram(int keyCode, char mappedKeyCode);
void sendPutCharToProgram(char input);
} // namespace programs