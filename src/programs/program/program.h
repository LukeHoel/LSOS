#ifndef PROGRAM_H
#define PROGRAM_H
#include "cstdio.h"
using namespace std;
namespace programs {
class Program {
public:
  void run(const char *programName = "");
  void drawBar(const char *programName);
  void drawTitle(const char *programName);
  virtual void main();
  virtual void exit();
  virtual void receiveKeyPress(int keyCode, char mappedKeyCode){};
};
} // namespace programs
#endif
