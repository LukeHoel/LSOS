#include "keymap.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

void kbInit(void)
{
	//0xFD is 11111101 - enables only IRQ1 (keyboard)
	writePort(0x21 , 0xFD);
}

void keyboardHandlerMain(void) {
	unsigned char status;
	char keycode;

	// write EOI 
	writePort(0x20, 0x20);

	status = readPort(KEYBOARD_STATUS_PORT);
	//Lowest bit of status will be set if buffer is not empty
	if (status & 0x01) {
		keycode = readPort(KEYBOARD_DATA_PORT);
		if(keycode < 0)
			return;
		//"raise" the char into an input handler
		raiseInputChar(keymap[(int)keycode]);
	}
}
