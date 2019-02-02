void failTest(char *message){
    	if(DEBUGMODE > DEBUGNONE){
		terminalPrintf("%s",message);
	}
}

#include "memory.c"

void runUnitTests(){
	testMemory();
}
