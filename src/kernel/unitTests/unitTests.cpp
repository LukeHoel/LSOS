void failTest(char *message){
    	if(DEBUGMODE > DEBUGNONE){
		terminalPrintf("%s\n",message);
	}
}

#include "memory.cpp"

void runUnitTests(){
	testMemory();
}
