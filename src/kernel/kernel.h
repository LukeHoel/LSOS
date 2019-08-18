#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define DEBUGNONE 0
#define DEBUGERRORS 1
#define DEBUGALL 2
#define DEBUGMODE DEBUGERRORS

const char *VERSION = "0.0.1";

// Externed asm functions
extern "C" char readPort(unsigned short port);
extern "C" void writePort(unsigned short port, unsigned char data);
extern "C" void loadIdt(unsigned long *idtptr);
extern "C" void keyboardHandler(void);
extern "C" void keyboardHandlerWrapper();
extern "C" void gdtFlush();

void idtInit(void);
void kbInit(void);
// interrupts
void mapInterrupts();

// tty
void ttyInit(void);
void setScreenEntry(char c, uint8_t color, size_t x, size_t y);
// Program manager
void sendKeypressToActiveProgram(int keyCode, char mappedKeyCode);
