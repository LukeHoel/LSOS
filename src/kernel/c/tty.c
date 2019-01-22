#include "vga.c"

size_t strlen(const char* str) 
{
        size_t len = 0;
        while (str[len])
                len++;
        return len;
}

size_t terminalRow;
size_t terminalColumn;
uint8_t terminalColor;
uint16_t* terminalBuffer;
 
void terminalInitialize(void) 
{
        terminalRow = 0;
        terminalColumn = 0;
        terminalColor = vgaEntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        terminalBuffer = (uint16_t*) 0xB8000;
        for (size_t y = 0; y < VGA_HEIGHT; y++) {
                for (size_t x = 0; x < VGA_WIDTH; x++) {
                        const size_t index = y * VGA_WIDTH + x;
                        terminalBuffer[index] = vgaEntry(' ', terminalColor);
                }
        }
}
 
void terminalSetColor(uint8_t color) 
{
        terminalColor = color;
}

size_t terminalIndex(size_t x, size_t y){
	return y * VGA_WIDTH + x;
}

void terminalPutEntryAt(char c, uint8_t color, size_t x, size_t y) 
{
        terminalBuffer[terminalIndex(x,y)] = vgaEntry(c, color);
}

void terminalPutChar(char c) 
{
        if(c == '\n'){
	    	//newline
	    	terminalRow ++;
                terminalColumn = 0;
        }
	else if(c == '\b'){
	    	//backspace
		if(terminalColumn > 0){
			terminalColumn --;
		}

		terminalPutEntryAt(' ', 0, terminalColumn, terminalRow);
	}
	else{
                //allow last character in line to be delete
	    	if(terminalColumn < VGA_WIDTH-1){
	    		terminalPutEntryAt(c, terminalColor, terminalColumn, terminalRow);
		}
		if(terminalColumn < VGA_WIDTH){
			terminalColumn ++;
		}
        }
}
 
void terminalWrite(const char* data, size_t size) 
{
        for (size_t i = 0; i < size; i++)
                terminalPutChar(data[i]);
}
 
void terminalWriteString(const char* data) 
{
        terminalWrite(data, strlen(data));
}

void printInt(int in){
        //simple mapping algorithm to char 
        char digits[10] = "0123456789";

        while(in > 9){
               terminalPutChar(digits[in % 10]);
               in /= 10;
        }
        terminalPutChar(digits[in]);
}

void kprintf(const char* data, ...){
       
        va_list arguments;
        va_start (arguments, data);

        for(size_t i = 0; i < strlen(data); i++){
                if(data[i] != '%'){
                        terminalPutChar(data[i]);        
                }
                else{
                        //go right ahead to next character
                        i++;
                        //switch to parser for whatever data type this is
                        switch(data[i]){
                                case('c'):
                                        terminalPutChar(va_arg(arguments, int));
                                    break;
                                case('s'):
        				terminalWriteString(va_arg(arguments, const char*));                                       
                                    break;
                                case('d'):
                                        printInt(va_arg(arguments, int));        
                                    break;
                        }

                }
        }

        va_end(arguments);
}
