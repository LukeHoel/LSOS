#include <cstdio.h>
void panic() {
  if (DEBUGMODE > DEBUGNONE) {
    printf("Double fault encountered. Hanging now...");
  }
  while (1)
    ;
}
