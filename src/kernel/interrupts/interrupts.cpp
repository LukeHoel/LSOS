void panic() {
  if (DEBUGMODE > DEBUGNONE) {
    terminalPrintf("Double fault encountered. Hanging now...");
  }
  while (1)
    ;
}
