void readLine(size_t rowNumber, char* lineContent){
	
	int foundEnd = 0;
	for(int i = VGA_WIDTH;i >= 0; i--){
	    	//get current line
	    	char current =  ttyBuffer[i + (VGA_WIDTH*rowNumber)];
		//code can for sure be optimized eventually...
	 	if(!foundEnd){
			if(current == ' '){
				lineContent[i] = 0;
			}
			else{
				foundEnd = 1;
			}
		}
		if(foundEnd){
			lineContent[i] = current;
		}
	}
}

struct command {
	int operation;
	char* data;
};

struct command parseLine(char* lineContent){
	struct command ret = {0,"placeholder"};
	return ret;
}

void processCommand(size_t rowNumber){

    //read the line into the lineContent variable
    char lineContent[VGA_WIDTH];
    readLine(rowNumber, lineContent);
    //send into parser
    struct command cmd = parseLine(lineContent);

    terminalPrintf("Commmand type is %d, command data is %s", cmd.operation, cmd.data);
}
