extern void keyboardHandlerWrapper();

void panic(){
	terminalPrintf("Double fault encountered. Hanging now...");
	while(1);
}
