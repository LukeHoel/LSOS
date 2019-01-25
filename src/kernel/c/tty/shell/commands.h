struct commandData{
    char words[VGA_WIDTH][VGA_WIDTH];
    size_t count;
};

struct command{
	char* name;
	void (*function)(struct commandData);
};

void echo(struct commandData data){
    	for(int i = 0; i < data.count; i ++){	
		terminalPrintf("%s ", data.words[i]);
	}
	terminalPrintf("\n");
}

struct command commands[] = {

    {"echo", &echo},

};

void decodeCommand(struct commandData data){
    commands[0].function(data);

}
