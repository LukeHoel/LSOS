size_t terminalRow;
size_t terminalColumn;

void terminalInit(void){
	terminalRow = 0;
	terminalColumn = 0;
}

void terminalPutChar(char c){
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
                terminalPutChar(data[i]);
}
 
void terminalWriteString(const char* data) 
{
        terminalWrite(data, strlen(data));
}

void printInt(int in){
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
