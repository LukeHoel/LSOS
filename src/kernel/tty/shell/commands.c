struct commandData{
    char words[VGA_WIDTH][VGA_WIDTH];
    size_t count;
};

struct command{
	char* name;
	void (*function)(struct commandData);
};

void echo(struct commandData data){
	//start at 1 because 0 is the command name
    	for(int i = 1; i < data.count; i ++){	
		terminalPrintf("%s ", data.words[i]);
	}
	terminalPrintf("\n");
}

#define amountCommands 2
struct command commands[amountCommands] = {
	{"echo", &echo}
};

void executeCommand(struct commandData data){
	for(int i = 0; i < amountCommands; i ++){
		//search for command match
		if(strcmp(data.words[0], commands[i].name) == 0){
			commands[i].function(data);
			return;
		}
	}
	//if it gets here, it couldn't find anything
	terminalPrintf("Command \'%s\' not found\n", data.words[0]);
}
