namespace shell {
class commandData {
public:
  char words[VGA_WIDTH][VGA_WIDTH];
  size_t count;
};

struct command {
  const char *name;
  void (*function)(commandData);
};

void info(commandData data) {
  terminalPutS("Simple OS ");
  terminalPutS("Version ");
  terminalPutS(VERSION);
  terminalPutS("\n");
}

void echo(commandData data) {
  // start at 1 because 0 is the command name
  for (size_t i = 1; i < data.count; i++) {
    terminalPutS(data.words[i]);
    terminalPutS(" ");
  }
  terminalPutChar('\n', true);
}

#define amountCommands 2
struct command commands[amountCommands] = {{"info", &info}, {"echo", &echo}};

void executeCommand(commandData data) {
  for (int i = 0; i < amountCommands; i++) {
    // search for command match
    if (strcmp(data.words[0], commands[i].name) == 0) {
      commands[i].function(data);
      return;
    }
  }
  // if it gets here, it couldn't find anything
  terminalPutS("Command not found\n");
}
} // namespace shell