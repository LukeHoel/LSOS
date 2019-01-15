#include "vga.h"
//#include "tty.h"

size_t strlen(const char* str) 
{
        size_t len = 0;
        while (str[len])
                len++;
        return len;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize(void) 
{
        terminal_row = 0;
        terminal_column = 0;
        terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        terminal_buffer = (uint16_t*) 0xB8000;
        for (size_t y = 0; y < VGA_HEIGHT; y++) {
                for (size_t x = 0; x < VGA_WIDTH; x++) {
                        const size_t index = y * VGA_WIDTH + x;
                        terminal_buffer[index] = vga_entry(' ', terminal_color);
                }
        }
}
 
void terminal_setcolor(uint8_t color) 
{
        terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
        const size_t index = y * VGA_WIDTH + x;
        terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
        if(c == '\n'){
                terminal_row ++;
                terminal_column = 0;
        }
        else{
                terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
                if (++terminal_column == VGA_WIDTH) {
                        terminal_column = 0;
                        if (++terminal_row == VGA_HEIGHT)
                                terminal_row = 0;
                }
        }
}
 
void terminal_write(const char* data, size_t size) 
{
        for (size_t i = 0; i < size; i++)
                terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
        terminal_write(data, strlen(data));
}

void printInt(int in){
        //simple mapping algorithm to char 
        char digits[10] = "0123456789";

        while(in > 9){
               terminal_putchar(digits[in % 10]);
               in /= 10;
        }
        terminal_putchar(digits[in]);
}

void kprintf(const char* data, ...);

void kprintf(const char* data, ...){
       
        va_list arguments;
        va_start (arguments, data);

        for(size_t i = 0; i < strlen(data); i++){
                if(data[i] != '%'){
                        terminal_putchar(data[i]);        
                }
                else{
                        //go right ahead to next character
                        i++;
                        //switch to parser for whatever data type this is
                        switch(data[i]){
                                case('c'):
                                        terminal_putchar(va_arg(arguments, int));
                                    break;
                                case('s'):
        				terminal_writestring(va_arg(arguments, const char*));                                       
                                    break;
                                case('d'):
                                        printInt(va_arg(arguments, int));        
                                    break;
                        }

                }
        }

        va_end(arguments);
}
