//utils
size_t strlen(const char*);
int strcmp(const char*, const char*);
//gdt
void gdt_install();
//idt
extern char readPort(unsigned short port);
extern void writePort(unsigned short port, unsigned char data);
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
const char* prompt = ">";
#define promptLength 1
void terminalInit(void);
void terminalPrintf(const char*, ...);
