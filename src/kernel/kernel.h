#include <cstdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

using namespace std;

#define DEBUGNONE 0
#define DEBUGERRORS 1
#define DEBUGALL 2
#define DEBUGMODE DEBUGERRORS

// utils
size_t strlen(const char *);
int strcmp(const char *, const char *);
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
