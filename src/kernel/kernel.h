//utils
size_t strlen(const char*);
//idt
void idtInit(void);
void kbInit(void);
//inputreceiver
void raiseInputChar(char);
//tty
void ttyInit(void);
void ttyPutEntryAt(char c, uint8_t color, size_t x, size_t y);
//terminal
#define INPUT_TYPE_INTERNAL 0
#define INPUT_TYPE_USER 1
void terminalInit(void);
void terminalPrintf(const char*, ...);
