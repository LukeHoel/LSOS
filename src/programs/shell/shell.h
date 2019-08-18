#ifndef TERMINAL_H
#define TERMINAL_H
using namespace std;
namespace shell {

const char *prompt = ">";
#define promptLength 1
// Random access point for use in commands. Not stable
char utilityWidthBuffer[VGA_WIDTH];
void clearUtilityWidthBuffer();
void terminalPrintPrompt();
void terminalScroll();
void terminalPutChar(char c, bool internal = false);
void terminalPutS(const char *input);
void main();
} // namespace shell
#endif