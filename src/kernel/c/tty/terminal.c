size_t terminalRow;
size_t terminalColumn;

#include "commandProcessor.c"

void terminalInit(void){
	terminalRow = 0;
	terminalColumn = 0;
}

void terminalPrintPrompt(){
	terminalPrintf("%s", prompt);
	//hide cursor offscreen
	updateCursor((VGA_WIDTH*VGA_HEIGHT)*-1,terminalRow);
}

void terminalScroll(){
	//shift the lines up by one
    	for(int y = 0; y < VGA_HEIGHT; y ++){
    		for(int x = 0; x < VGA_WIDTH; x ++){
			ttyBuffer[ttyIndex(x,y)] = ttyBuffer[ttyIndex(x,y+1)];
		}	
	}
}

void terminalPutChar(char c, int type){
        if(c == '\n'){
	    	//newline
	    	if(terminalRow < VGA_HEIGHT-1){
	    		terminalRow ++;
		}else{
			terminalScroll();
		}
                
		terminalColumn = 0;

	    	if(type == INPUT_TYPE_USER){
			processCommand(terminalRow - 1);
			terminalPrintPrompt();
		}
        }
	else if(c == '\b'){
	    	//backspace
	    	if(type == INPUT_TYPE_USER && terminalColumn <= promptLength){
		    return;
		}
		if(terminalColumn > 0){
			terminalColumn --;
		}

		ttyPutEntryAt(' ', 0, terminalColumn, terminalRow);
	}
	else{
                //allow last character in line to be delete
	    	if(terminalColumn < VGA_WIDTH-1){
	    		ttyPutEntryAt(c, ttyColor, terminalColumn, terminalRow);
		}
		if(terminalColumn < VGA_WIDTH){
			terminalColumn ++;
		}
        }
}

void terminalWrite(const char* data, size_t size) {
        for (size_t i = 0; i < size; i++)
                terminalPutChar(data[i], INPUT_TYPE_INTERNAL);
}
 
void terminalWriteString(const char* data) 
{
        terminalWrite(data, strlen(data));
}

void printInt(int in){
        char digits[10] = "0123456789";

        while(in > 9){
               terminalPutChar(digits[in % 10], INPUT_TYPE_INTERNAL);
               in /= 10;
        }
        terminalPutChar(digits[in], INPUT_TYPE_INTERNAL);
}

void terminalPrintf(const char* data, ...){
       
        va_list arguments;
        va_start (arguments, data);

        for(size_t i = 0; i < strlen(data); i++){
                if(data[i] != '%'){
                        terminalPutChar(data[i], INPUT_TYPE_INTERNAL);        
                }
                else{
                        //go right ahead to next character
                        i++;
                        //switch to parser for whatever data type this is
                        switch(data[i]){
                                case('c'):
                                        terminalPutChar(va_arg(arguments, int), INPUT_TYPE_INTERNAL);
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
