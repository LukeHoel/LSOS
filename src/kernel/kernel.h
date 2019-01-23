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
void terminalInit(void);
void kprintf(const char*, ...);
