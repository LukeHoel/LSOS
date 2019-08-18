namespace programs {
void runProgram(const char *name);
void sendKeypressToActiveProgram(int keyCode, char mappedKeyCode);
void sendPutCharToProgram(char input);
} // namespace programs