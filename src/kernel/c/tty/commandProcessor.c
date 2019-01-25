#include "shell/commands.h"

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

//takes in string, outputs split string by spaces, returns int
int splitCommand(char* lineContent, char splitContent[VGA_WIDTH][VGA_WIDTH]){
	
	int i = 0;
	int j = 0;
	for(int k = 0; k < strlen(lineContent); k ++){
		
		if(lineContent[k] == ' '){
	    		//end string with null terminator
		    	splitContent[i][j] = '\0';
			i ++;
			j = 0;
		}
		else{
	    		splitContent[i][j ++] = lineContent[k];
		}
	}
	

	//add null terminator to end	
	splitContent[i][j] = '\0';
	return i+1;
}

void processCommand(size_t rowNumber){

    	//read the line into the lineContent variable
    	char lineContent[VGA_WIDTH];
    	readLine(rowNumber, lineContent);
    	//send into parser
 	struct commandData data;
	data.count = splitCommand(lineContent, data.words);
	decodeCommand(data);	
	
}
