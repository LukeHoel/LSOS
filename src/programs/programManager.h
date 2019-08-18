
enum Programs { _shell = 1, _editor = 2 };

int currentProgram = 0;
void runProgram(const char *name);
void sendKeypressToActiveProgram(int keyCode, char mappedKeyCode);
void sendPutCharToProgram(char input);