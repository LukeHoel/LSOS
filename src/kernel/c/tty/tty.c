#include "vga.c"

uint8_t ttyColor;
uint16_t* ttyBuffer;

void ttyInit(void) 
{
        ttyColor = vgaEntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        ttyBuffer = (uint16_t*) 0xB8000;
        for (size_t y = 0; y < VGA_HEIGHT; y++) {
                for (size_t x = 0; x < VGA_WIDTH; x++) {
                        const size_t index = y * VGA_WIDTH + x;
                        ttyBuffer[index] = vgaEntry(' ', ttyColor);
                }
        }
}
 
void ttySetColor(uint8_t color) 
{
        ttyColor = color;
}

size_t ttyIndex(size_t x, size_t y){
	return y * VGA_WIDTH + x;
}

void ttyPutEntryAt(char c, uint8_t color, size_t x, size_t y) 
{
        ttyBuffer[ttyIndex(x,y)] = vgaEntry(c, color);
}
