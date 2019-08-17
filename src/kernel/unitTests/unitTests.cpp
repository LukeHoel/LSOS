void failTest(const char *message) {
  if (DEBUGMODE > DEBUGNONE) {
    printf("%s\n", message);
  }
}

#include "memory.cpp"

void runUnitTests() { testMemory(); }
