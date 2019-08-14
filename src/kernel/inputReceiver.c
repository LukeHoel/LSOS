//choose what to do depending on system state
void raiseInputChar(char input){
    	if(input > 0){
    		terminalPutChar(input, INPUT_TYPE_USER);	
	}
}
