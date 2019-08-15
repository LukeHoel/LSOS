namespace shell {
void echo(commandData data) {
  // start at 1 because 0 is the command name
  for (int i = 1; i < data.count; i++) {
    terminalPrintf("%s ", data.words[i]);
  }
  terminalPrintf("\n");
}

// induce an exception
void divideByZero(commandData data) { int i = 1 / 0; }
} // namespace shell