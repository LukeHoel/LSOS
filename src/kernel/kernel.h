#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#define DEBUGNONE 0
#define DEBUGERRORS 1
#define DEBUGALL 2
#define DEBUGMODE DEBUGERRORS

//utils
size_t strlen(const char*);
int strcmp(const char*, const char*);
// Externed asm functions
extern "C" char readPort(unsigned short port);
extern "C" void writePort(unsigned short port, unsigned char data);
extern "C" void loadIdt(unsigned long *idtptr);
extern "C" void keyboardHandler(void);
extern "C" void keyboardHandlerWrapper();
extern "C" void gdtFlush();

void idtInit(void);
void kbInit(void);
//interrupts
void mapInterrupts();

//inputreceiver
void raiseInputChar(char);
//tty
void ttyInit(void);
void ttyPutEntryAt(char c, uint8_t color, size_t x, size_t y);
//terminal
#define INPUT_TYPE_INTERNAL 0
#define INPUT_TYPE_USER 1
const char* prompt = ">";
#define promptLength 1
void terminalInit(void);
void terminalPrintf(const char*, ...);
//memory
void *malloc(size_t);
void free(void *ptr);
